#include "UiManager.h"
#include "../../Core/Components/ComponentFactory.h"


void UiManager::load(GLFWwindow *window, FrameBufferGL & frameBuffer) {
    textureId = frameBuffer.getTexture();
    textureHeight = frameBuffer.getTextureHeight();
    textureWidth = frameBuffer.getTextureWidth();

    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO & io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigWindowsMoveFromTitleBarOnly = true;

    this->io = &io;

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 450 core");
    // Setup Dear ImGui style
    ImGui::StyleColorsClassic();
}

ImGuiIO *UiManager::getIo() {
    return io;
}

bool UiManager::getOnSceneUi() const {
    return onSceneUi;
}

void UiManager::update() {
    // feed inputs to dear imgui, start new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UiManager::render(Scene & scene) {
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
    mainMenuBar();
    objectHierarchy(scene);
    sceneWindow();

    if( selectedObject != nullptr )
        components(selectedObject);

    //ImGui::ShowDemoWindow();


    // Render dear imgui into screen
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UiManager::terminate() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UiManager::mainMenuBar() {
    ImGui::BeginMainMenuBar();
    ImGui::MenuItem("File");
    ImGui::MenuItem("Edit");
    ImGui::MenuItem("View");
    ImGui::EndMainMenuBar();
}

void UiManager::objectHierarchy(Scene &scene) {
    ImGui::Begin("Hierarchy", nullptr);
    ImGui::SetWindowSize(ImVec2((float)300, (float)windowHeight));

    if(ImGui::Button("Add Object")){
        scene.addObject();
    }

    ImGui::Separator();

    for(auto & object : scene.getObjects())
    {
        const char * name = object->getName().c_str();
        if (ImGui::Selectable(name))
        {
            selectedObject = object.get();
        }

    }

    ImGui::End();

}

void UiManager::components(Object* object) {
    const char * title = object->getName().c_str();
    ImGui::Begin("Components", nullptr);

    ImGui::SetWindowSize(ImVec2((float)300, (float)500));

    ImGui::SetCursorPosX(110);
    ImGui::Text(title);

    ImGui::Separator();
    ImGui::Spacing();
    ImGui::Spacing();

    //ImGui::Text(std::to_string(object->getTransform().getPosition().x).c_str());

    ImGui::Text("Transform");

    ImGui::Spacing();
    ImGui::Spacing();

    float posXBefore = object->getTransform().getPosition().x;
    float posYBefore = object->getTransform().getPosition().y;
    float posZBefore = object->getTransform().getPosition().z;

    float posXAfter = object->getTransform().getPosition().x;
    float posYAfter = object->getTransform().getPosition().y;
    float posZAfter = object->getTransform().getPosition().z;

    ImGui::InputFloat("X",&posXAfter);
    ImGui::InputFloat("Y",&posYAfter);
    ImGui::InputFloat("Z",&posZAfter);

    if(posXAfter != posXBefore || posYAfter != posYBefore || posZAfter != posZBefore){
        object->getTransform().setPosition(posXAfter,posYAfter,posZAfter);
    }

    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::Separator();
    ImGui::Spacing();
    ImGui::Spacing();

    static const char* current_item = "ADD COMPONENT";
    if (ImGui::BeginCombo("##combo", current_item)){
        for (auto & Component : ComponentFactory::m_map)
        {
            bool is_selected = (current_item == Component.first.c_str()); // You can store your selection however you want, outside or inside your objects
            if (ImGui::Selectable(Component.first.c_str(), is_selected))
                current_item = Component.first.c_str();
            if (is_selected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }

    ImGui::SameLine();

    // adding components
    if(ImGui::Button("+")){
        if(strcmp(current_item,"ADD COMPONENT")!=0){
            Component * newComponent = ComponentFactory::Create(current_item);
            newComponent->load(object);
        }
    }

    ImGui::Spacing();
    ImGui::Spacing();

    for(auto & component : object->getComponents()){
        const char * name = component->getName().c_str();
        if(ImGui::TreeNode(name)){
            if(strcmp(name,"mesh")==0){
                meshCOptions(dynamic_cast<MeshC*>(component));
            }
            ImGui::TreePop();
        }

        ImGui::Spacing();
        ImGui::Spacing();
    }
    ImGui::End();
}

void UiManager::sceneWindow() {
    ImGui::Begin("Scene Window");

    onSceneUi = ImGui::IsWindowHovered();

    ImGui::GetWindowDrawList()->AddImage(
            (void*)textureId, ImVec2(ImGui::GetCursorScreenPos()),
            ImVec2(ImGui::GetCursorScreenPos().x + textureWidth, ImGui::GetCursorScreenPos().y + textureHeight), ImVec2(0, 1), ImVec2(1, 0)
            );

    ImGui::End();
}

void UiManager::meshCOptions(MeshC * meshC) {
    static const char* current_mesh = "tore";
    const char * meshes[] = {
            "tore",
            "cube",
            "sphere",
            "icosahedron"
    };
    if (ImGui::BeginCombo("##combo", current_mesh))
    {
        for (auto & mesh : meshes){
            bool is_selected = (current_mesh == mesh); // You can store your selection however you want, outside or inside your objects
            if (ImGui::Selectable(mesh, is_selected))
                current_mesh = mesh;
            if (is_selected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }

    ImGui::SameLine();
    if (ImGui::Button("Set"))
    {
        std::cout<< current_mesh[0] << std::endl;
        meshC->reloadMesh(meshC->getOwner(),current_mesh[0]);
    }
}

