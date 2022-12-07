#ifndef ENGINE_H
#define ENGINE_H

#include "Window.h"
#include "DefaultScene.h"
#include "EngineRendererGL.h"
#include "UI/UiManager.h"

class Engine{
private:
    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    UiManager ui;

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
