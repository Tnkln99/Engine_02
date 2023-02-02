#ifndef ENGINE_02_WINDOW_H
#define ENGINE_02_WINDOW_H


#include <iostream>
#include "UI/UiManager.h"
#include "BackEnd/ScreenFbo.h"
#include "BackEnd/Renderer.h"


class Window{
private:
    int windowWidth{};
    int windowHeight{};
    GLFWwindow* window{};

    ScreenFbo screenFbo{};

    UiManager ui;
    Renderer renderer;
public:
    void load();

    void loadUi();
    void render(Scene & scene);
    void update();

    void getInputs();
    bool shouldClose();

    [[nodiscard]] float getHeight() const;
    [[nodiscard]] float getWidth() const;
    [[nodiscard]] GLFWwindow* getPointer() const;
    [[nodiscard]] bool canGetSceneInput() const;
    [[nodiscard]] glm::vec2 getSceneWindowSize() const;

    void setHeight(int height);
    void setWidth(int width);

    void clean();
};


#endif //ENGINE_02_WINDOW_H
