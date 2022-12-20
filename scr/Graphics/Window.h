#ifndef ENGINE_02_WINDOW_H
#define ENGINE_02_WINDOW_H


#include <iostream>
#include "Framebuffer.h"


class Window{
private:
    int windowWidth;
    int windowHeight;
    GLFWwindow* window;

    Framebuffer framebuffer;
public:
    void load();

    void getInputs();
    bool shouldClose();

    [[nodiscard]] float getHeight() const;
    [[nodiscard]] float getWidth() const;
    [[nodiscard]] GLFWwindow* getPointer() const;

    void setHeight(int height);
    void setWidth(int width);
    void setBackgroundColor(float r, float b, float g,float t);

    void swapBuffer();
    void clearBuffer();
    void drawToFrameBuffer();
    void bindToFrameBuffer();

    int getRenderTexture();

    void getEvents();

    void clean();
};


#endif //ENGINE_02_WINDOW_H
