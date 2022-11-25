#ifndef SNAKE_ENGINE_H
#define SNAKE_ENGINE_H

#include "scenes/Scene02_VertexNormals.h"
#include "Window.h"

class Engine{
private:
    Window window;
    bool engineRunning = true;

    Scene02_VertexNormals scene;
public:
    Engine();

    void run();
    void terminate();

    void update();
};

#endif
