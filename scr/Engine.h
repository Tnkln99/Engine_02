#ifndef ENGINE_H
#define ENGINE_H

#include "Graphics/Window.h"
#include "Core/Scene.h"
#include "Core/Components/ComponentFactory.h"

class Engine{
private:
    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    Window window;
    bool engineRunning = true;

    Scene scene;
public:
    Engine();

    void run();
    void terminate();

    void update();
};

#endif
