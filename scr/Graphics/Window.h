#ifndef ENGINE_02_WINDOW_H
#define ENGINE_02_WINDOW_H


#include <iostream>
#include "../UI/UiManager.h"
#include "Framebuffer.h"
#include "EngineRendererGL.h"


class Window{
private:
    int windowWidth;
    int windowHeight;
    GLFWwindow* window;

    Framebuffer framebuffer;
    UiManager ui;
    EngineRendererGL renderer;
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

    void setHeight(int height);
    void setWidth(int width);
    void setBackgroundColor(float r, float b, float g,float t);

    void swapBuffer();
    void clearBuffer();

    void getEvents();

    void clean();
};


#endif //ENGINE_02_WINDOW_H
