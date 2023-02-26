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

    void light(Scene & scene);

    void PushImageVarSwizzle(GLuint* textureId)
    {
        ImGui::GetWindowDrawList()->AddCallback(
                [](const ImDrawList* parent_list, const ImDrawCmd* cmd)
                {
                    glBindTexture(GL_TEXTURE_2D, *reinterpret_cast<GLuint*>(cmd->UserCallbackData));
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_RED);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_RED);

                }, textureId
        );
    }

    void PopImageVarSwizzle()
    {
        ImGui::GetWindowDrawList()->AddCallback(
                [](const ImDrawList* parent_list, const ImDrawCmd* cmd)
                {
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_GREEN);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_BLUE);
                }, nullptr
        );
    }

    void modelCOptions(ModelC * modelC);

    void terminate();
};


#endif //ENGINE_02_UIMANAGER_H
