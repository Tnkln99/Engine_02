#ifndef SNAKE_ENGINE_H
#define SNAKE_ENGINE_H

#include "scenes/Scene05_LightSandBox.h"
#include "Window.h"

class Engine{
private:
    Window window;
    bool engineRunning = true;

    Scene05_LightSandBox scene;
public:
    Engine();

    void run();
    void terminate();

    void update();
};

#endif
