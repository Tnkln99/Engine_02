#include "Engine.h"

Engine::Engine() {
    window.load();

    scene.load(window.getPointer());
}

void Engine::run() {
    while (engineRunning)
    {
        window.setBackgroundColor(0.07f, 0.13f, 0.17f, 1.0f);
        window.clearBuffer();

        update();
        renderer.drawAll(scene);

        window.swapBuffer();
        window.getEvents();
    }
    terminate();
}

void Engine::terminate() {
    //scene.clean();
    // Delete window before ending the program
    window.clean();
    renderer.cleanRenderer();
}

void Engine::update() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if(window.shouldClose()){
        engineRunning = false;
    }
    window.getInputs();
    scene.addInput(window.getPointer(), deltaTime);

    scene.update(deltaTime);
}
