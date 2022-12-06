#ifndef ENGINE_H
#define ENGINE_H

#include "Window.h"
#include "Scenes/DefaultScene.h"
#include "EngineRendererGL.h"

class Engine{
private:
    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    Window window;
    bool engineRunning = true;

    DefaultScene scene;

    EngineRendererGL renderer;
public:
    Engine();

    void run();
    void terminate();

    void update();
};

#endif
