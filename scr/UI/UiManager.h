#ifndef ENGINE_02_UIMANAGER_H
#define ENGINE_02_UIMANAGER_H

#include "../Core/Scene.h"
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

class UiManager {
private:
    ImGuiIO * io;

    Object * selectedObject = nullptr;

    int windowWidth;
    int windowHeight;
public:
    UiManager() = default;

    void load(GLFWwindow * window);

    ImGuiIO * getIo();

    void update();

    void render(Scene & scene);

    void mainMenuBar();
    void objectHierarchy(Scene & scene);
    void components(Object * object);

    void sceneWindow();

    void terminate();
};


#endif //ENGINE_02_UIMANAGER_H
