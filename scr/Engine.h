#ifndef SNAKE_ENGINE_H
#define SNAKE_ENGINE_H

#include "scenes/Scene01_TessGeomShaders.h"
#include "Window.h"

class Engine{
private:
    Window window;
    bool engineRunning = true;


    Scene01_TessGeomShaders scene;
public:
    Engine();

    void run();
    void terminate();

    void update();
};

#endif
