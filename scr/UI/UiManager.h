#ifndef ENGINE_02_UIMANAGER_H
#define ENGINE_02_UIMANAGER_H

#include "../Core/Scene.h"
#include "../Graphics/Framebuffer.h"
#include <imgui_impl_opengl3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>

class UiManager {
private:
    ImGuiIO * io;

    Object * selectedObject = nullptr;

    bool onSceneUi = true;

    int windowWidth;
    int windowHeight;

    int textureId;
    int textureWidth;
    int textureHeight;
public:
    UiManager() = default;

    void load(GLFWwindow * window, Framebuffer & frameBuffer);

    ImGuiIO * getIo();
    [[nodiscard]] bool getOnSceneUi() const;

    void update();

    void render(Scene & scene);

    void mainMenuBar();
    void objectHierarchy(Scene & scene);
    void components(Object * object);

    void sceneWindow();

    void terminate();
};


#endif //ENGINE_02_UIMANAGER_H
