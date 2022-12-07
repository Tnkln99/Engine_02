#ifndef ENGINE_02_UIMANAGER_H
#define ENGINE_02_UIMANAGER_H

#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include "GLFW/glfw3.h"

class UiManager {
private:
    ImGuiIO * io;
public:
    UiManager() = default;

    void load(GLFWwindow * window);

    ImGuiIO * getIo();

    void update();

    void render();

    void terminate();
};


#endif //ENGINE_02_UIMANAGER_H
