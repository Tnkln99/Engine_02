#include "Engine.h"

Engine::Engine() {
    window.load();

    scene.load(window.getWidth(), window.getHeight());
}

void Engine::run() {
    while (engineRunning)
    {
        window.setBackgroundColor(0.07f, 0.13f, 0.17f, 1.0f);
        window.clearBuffer();

        update();
        scene.draw();

        window.swapBuffer();
        window.getEvents();
    }
    terminate();
}

void Engine::terminate() {
    scene.clean();
    // Delete window before ending the program
    window.clean();
}

void Engine::update() {
    if(window.shouldClose()){
        engineRunning = false;
    }
    window.getInputs();
    scene.update();
}
