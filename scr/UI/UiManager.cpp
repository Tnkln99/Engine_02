#include "UiManager.h"
#include "../Components/ComponentFactory.h"


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
    objectHierarchy(scene);
    // Render dear imgui into screen
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UiManager::terminate() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UiManager::objectHierarchy(Scene &scene) {
    ImGui::Begin("Hierarchy", nullptr, ImGuiWindowFlags_NoMove);
    ImGui::SetWindowSize(ImVec2((float)300, (float)windowHeight));

    if(ImGui::Button("Add Object")){
        scene.addObject();
    }

    ImGui::Separator();

    for(auto & object : scene.getObjects()) {
        const char * name = object->getName().c_str();
        if (ImGui::TreeNode(name)){

            components(object);

            //ImGui::MenuItem("Child");

            ImGui::TreePop();
        }
    }

    ImGui::End();
}

void UiManager::components(Object * object) {
    const char * title = object->getName().c_str();
    ImGui::Begin(title,nullptr);
    ImGui::SetWindowSize(ImVec2((float)300, (float)500));
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
        Component * newComponent = ComponentFactory::Create(current_item);
        newComponent->load(object);
    }

    ImGui::Separator();
    ImGui::Spacing();
    ImGui::Spacing();

    for(auto & component : object->getComponents()){
        const char * name = component->getName().c_str();
        ImGui::TextWrapped("%s", name);

        if (strcmp(name, "mesh") == 0){

        }

        ImGui::Spacing();
        ImGui::Spacing();
    }
    ImGui::End();
}


