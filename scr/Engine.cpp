#include "Engine.h"
#include "GLFW/glfw3.h"


Engine::Engine() {
    window.load();

    scene.load(window.getPointer());

    ui.load(window.getPointer());
}

void Engine::run() {
    while (engineRunning)
    {
        window.setBackgroundColor(0.07f, 0.13f, 0.17f, 1.0f);
        window.clearBuffer();

        update();
        renderer.forwardRender(scene);
        ui.render(scene);

        window.swapBuffer();
        window.getEvents();
    }
    terminate();
}

void Engine::terminate() {
    ui.terminate();
    renderer.cleanRenderer();
    window.clean();
    ComponentFactory::clear();
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


