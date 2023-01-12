#include "Engine.h"


Engine::Engine() {
    window.load();

    scene.load(window.getPointer());

    window.loadUi();
}

void Engine::run() {
    while (engineRunning)
    {
        update();

        window.render(scene);
    }
    terminate();
}

void Engine::terminate() {
    window.clean();
    ComponentFactory::clear();
}

void Engine::update() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if(window.shouldClose()){
        engineRunning = false;
    }

    window.update();

    window.getInputs();
    if (window.canGetSceneInput())
        scene.addInput(window.getPointer(), deltaTime);

    scene.update(deltaTime);
}
