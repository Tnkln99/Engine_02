#include "UiManager.h"
#include "../Core/Components/ComponentFactory.h"


void UiManager::load(GLFWwindow *window) {
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO & io = ImGui::GetIO();

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

void UiManager::update() {
    // feed inputs to dear imgui, start new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UiManager::render(Scene & scene) {
    mainMenuBar();
    objectHierarchy(scene);

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
    ImGui::Begin("Hierarchy", nullptr,ImGuiWindowFlags_NoMove);
    ImGui::SetWindowSize(ImVec2((float)300, (float)windowHeight));

    if(ImGui::Button("Add Object")){
        scene.addObject();
    }

    ImGui::Separator();

    for(auto & object : scene.getObjects()) {
        const char * name = object->getName().c_str();
        if (ImGui::Selectable(name)){
            selectedObject = object.get();
        }
    }

    ImGui::End();

}

void UiManager::components(Object* object) {
    const char * title = object->getName().c_str();
    ImGui::Begin("components", nullptr,ImGuiWindowFlags_NoMove);

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
            ImGui::TreePop();
        }

        ImGui::Spacing();
        ImGui::Spacing();
    }
    ImGui::End();
}

void UiManager::sceneWindow() {
    ImGui::Begin("Scene Window");

    ImVec2 pos = ImGui::GetCursorScreenPos();

    ImGui::GetWindowDrawList()->AddImage(
            (void*)2, ImVec2(ImGui::GetCursorScreenPos()),
            ImVec2(ImGui::GetCursorScreenPos().x + 800/2, ImGui::GetCursorScreenPos().y + 800/2), ImVec2(0, 1), ImVec2(1, 0)
            );

    ImGui::End();
}

