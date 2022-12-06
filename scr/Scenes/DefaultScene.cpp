#include "DefaultScene.h"
#include "../EngineCamera.h"
#include "../MeshRenderer.h"

DefaultScene::DefaultScene() { }

DefaultScene::~DefaultScene(){

}

void DefaultScene::load(GLFWwindow * window){
    Assets::loadMaterial("../shaders/default.vert", "../shaders/default.frag", "", "", "", "Default");

    mainObject = new Object {this, 0.0f, 0.0f, -5.0f, "object"};
    new Mesh(mainObject);
    new MeshRenderer{mainObject};

    camera = new EngineCamera(window);
}

void DefaultScene::update(float dt) {
    camera->update();
    for (auto & object : objects){
        object->updateComponents(dt);
    }
}

void DefaultScene::addInput(GLFWwindow *window, float dt) { 
    camera->getCameraInput(window, dt);
}




