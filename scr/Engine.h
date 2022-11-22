#ifndef SNAKE_ENGINE_H
#define SNAKE_ENGINE_H

#include "scenes/Scene03_ToSphere.h"
#include "Window.h"

class Engine{
private:
    Window window;
    bool engineRunning = true;

    Scene03_ToSphere scene;
public:
    Engine();

    void run();
    void terminate();

    void update();
};

#endif
