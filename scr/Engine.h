#ifndef SNAKE_ENGINE_H
#define SNAKE_ENGINE_H

#include "scenes/Scene04_CameraSandBox.h"
#include "Window.h"

class Engine{
private:
    Window window;
    bool engineRunning = true;

    Scene04_CameraSandBox scene;
public:
    Engine();

    void run();
    void terminate();

    void update();
};

#endif
