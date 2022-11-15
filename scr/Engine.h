#ifndef SNAKE_ENGINE_H
#define SNAKE_ENGINE_H

#include <vector>

#include <chrono>
#include "Assets.h"
#include "GLFW/glfw3.h"
#include "Log.h"
#include "Mesh.h"

class Object;

class Engine{
private:
    float windowWidth{800};
    float windowHeight{800};
    GLFWwindow* window{};

    Matrix4 projMatrix;
    Shader shader;

    bool showNormals;

    Mesh mesh;
    Object* object;
public:
    Engine();

    void run();
    void terminate();

    void loadWindow();
    void update();
    void draw();

    void changeViewMode();

    [[nodiscard]] GLFWwindow* getWindow() const;
};

#endif //SNAKE_ENGINE_H
