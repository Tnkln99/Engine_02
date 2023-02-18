#ifndef ENGINE_02_UIMANAGER_H
#define ENGINE_02_UIMANAGER_H

#include "../../Core/Scene.h"
#include "../BackEnd/FBO.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "../../Utils/FileSearch.h"

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

    std::vector<std::string> objFiles = FileSearch::findObjFiles();
public:
    UiManager() = default;

    void load(GLFWwindow * window, FBO & frameBuffer);

    ImGuiIO * getIo();
    [[nodiscard]] bool getOnSceneUi() const;

    void update();

    void render(Scene & scene);

    void mainMenuBar();
    void objectHierarchy(Scene & scene);
    void components(Object * object);
    void sceneWindow();
    void assets();

    void modelCOptions(ModelC * modelC);
    void modelRendererCOptions(ModelRendererC * modelRendererC);

    void terminate();
};


#endif //ENGINE_02_UIMANAGER_H
