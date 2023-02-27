#include "UiManager.h"
#include "../../Core/Components/Utils/ComponentFactory.h"

void UiManager::load(GLFWwindow *window, FBO & frameBuffer) {
    textureId = *frameBuffer.getTexture();
    textureHeight = frameBuffer.getTextureHeight();
    textureWidth = frameBuffer.getTextureWidth();

    objFiles = FileSearch::findObjFiles();

    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

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
    assets();
    sceneWindow();

    light(scene);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_GREEN);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_BLUE);

    if( selectedObject != nullptr )
        components(selectedObject);

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
    ImGui::Begin("Hierarchy");

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

    ImGui::PushItemWidth(50);
    ImGui::InputFloat("Pos X",&posXAfter);
    ImGui::SameLine();
    ImGui::InputFloat("Pos Y",&posYAfter);
    ImGui::SameLine();
    ImGui::InputFloat("Pos Z",&posZAfter);
    ImGui::PopItemWidth();

    if(posXAfter != posXBefore || posYAfter != posYBefore || posZAfter != posZBefore){
        object->getTransform().setPosition(posXAfter,posYAfter,posZAfter);
        object->updatePositionMessageSent();
    }


    float scaleXBefore = object->getTransform().getScale().x;
    float scaleYBefore = object->getTransform().getScale().y;
    float scaleZBefore = object->getTransform().getScale().z;

    float scaleXAfter = object->getTransform().getScale().x;
    float scaleYAfter = object->getTransform().getScale().y;
    float scaleZAfter = object->getTransform().getScale().z;

    ImGui::PushItemWidth(50);
    ImGui::InputFloat("Scale X",&scaleXAfter);
    ImGui::SameLine();
    ImGui::InputFloat("Scale Y",&scaleYAfter);
    ImGui::SameLine();
    ImGui::InputFloat("Scale Z",&scaleZAfter);
    ImGui::PopItemWidth();

    if(scaleXAfter != scaleXBefore || scaleYAfter != scaleYBefore || scaleZAfter != scaleZBefore){
        object->getTransform().setScale(scaleXAfter,scaleYAfter,scaleZAfter);
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
            // After getting the component we should load it with the object
            newComponent->load(object);
        }
    }

    ImGui::Spacing();
    ImGui::Spacing();

    for(auto & component : object->getComponents()){
        const char * name = component->getName().c_str();
        if(ImGui::TreeNode(name)){
            if(strcmp(name,"model")==0){
                modelCOptions(dynamic_cast<ModelC*>(component));
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


void UiManager::light(Scene & scene) {
    ImGui::Begin("Light");
    int lightNo = 0;
    for(auto & light : scene.getLights()){
        std::string nameOfLight = "light " + std::to_string(lightNo);
        if(ImGui::TreeNode(nameOfLight.c_str())){
            ImGui::Begin(nameOfLight.c_str());
            PushImageVarSwizzle(light->shadowMap.getTexture());
            ImGui::Image((void*)light->shadowMap.getTexture(), { (float)light->shadowMap.getTextureWidth(), (float)light->shadowMap.getTextureHeight() }, { 0.0f, 1.0f }, { 1.0f, 0.0f }); // Or whatever dimensions you want
            PopImageVarSwizzle();
            ImGui::TreePop();
        }
        lightNo++;
    }
    ImGui::End();
}


void UiManager::assets() {
    ImGui::Begin("Assets", nullptr);

    ImGui::End();
}

void UiManager::modelCOptions(ModelC * modelC) {
    const char* items[objFiles.size()];
    for(int i = 0; i < objFiles.size();++i){
        items[i] = objFiles[i].c_str();
    }

    static const char* current_item = NULL;

    if (ImGui::BeginCombo("##combo", current_item)) // The second parameter is the label previewed before opening the combo.
    {
        for (int n = 0; n < IM_ARRAYSIZE(items); n++)
        {
            bool is_selected = (current_item == items[n]); // You can store your selection however you want, outside or inside your objects
            if (ImGui::Selectable(items[n], is_selected)) {
                current_item = items[n];
            }
            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }

    ImGui::SameLine();
    if (ImGui::Button("Set"))
    {
        //FileSearch::findObjFiles();
        modelC->reloadModel(modelC->getOwner(),current_item);
    }

    static bool showNormals = false;
    ImGui::Checkbox("Show normals", &showNormals);
    modelC->setNormalShow(showNormals);
}


