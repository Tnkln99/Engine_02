#ifndef ENGINE_02_WINDOW_H
#define ENGINE_02_WINDOW_H

#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "Log.h"
#include <iostream>


class Window{
private:
    float windowWidth{800};
    float windowHeight{800};
    GLFWwindow* window{};
public:
    void getInputs();
    bool shouldClose();

    [[nodiscard]] float getHeight() const;
    [[nodiscard]] float getWidth() const;

    void setHeight(float height);
    void setWidth(float width);
    void setBackgroundColor(float r, float b, float g,float t);

    void swapBuffer();
    void clearBuffer();

    void getEvents();

    void load();

    void clean();
};


#endif //ENGINE_02_WINDOW_H
