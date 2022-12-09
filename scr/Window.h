#ifndef ENGINE_02_WINDOW_H
#define ENGINE_02_WINDOW_H

#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "Log.h"
#include <iostream>


class Window{
private:
    int windowWidth;
    int windowHeight;
    GLFWwindow* window;
public:
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

    void getEvents();

    void load();

    void clean();
};


#endif //ENGINE_02_WINDOW_H
