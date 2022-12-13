#include "Engine.h"
#include "Components/MeshRendererC.h"
#include <GLFW/glfw3.h>


Engine::Engine() {
    window.load();

    scene.load(window.getPointer());

    ui.load(window.getPointer());
}

void Engine::run() {
    while (engineRunning)
    {
        window.getEvents();
        window.setBackgroundColor(0.07f, 0.13f, 0.17f, 1.0f);
        window.clearBuffer();

        update();
        renderer.drawAll(scene);
        ui.render(scene);

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
    ui.terminate();
}

void Engine::update() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    ui.update();

    if(window.shouldClose()){
        engineRunning = false;
    }


    window.getInputs();

    if(!ui.getIo() -> WantCaptureMouse)
        scene.addInput(window.getPointer(), deltaTime);

    scene.update(deltaTime);
}


