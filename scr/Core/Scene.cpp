#include "Scene.h"
#include "EngineCamera.h"
#include "Components/Utils/ComponentFactory.h"

void loadComponents(){
    ComponentFactory::Register("Model", new ModelC);
    ComponentFactory::Register("Light", new LightC);
}

Scene::Scene() { }

Scene::~Scene() { }

void Scene::load(GLFWwindow * window, float sceneWidth, float sceneHeight){
    loadComponents();

    camera = std::make_unique<EngineCamera>(window, sceneWidth, sceneHeight, 0,0,20);

    // DEBUG ----------------------------------------------------------------------------- //
    auto * cube = new Object(this,0,0,0,"Game Object");
    auto model = new ModelC;
    model->load(cube);

    auto * light = new Object(this,0,0,10,"Sun");
    auto lightC = new LightC;
    lightC->load(light);

    /*auto * light2 = new Object(this,0,0,-10,"Sun2");
    auto lightC2 = new LightC;
    lightC2->load(light2);*/
}

EngineCamera *Scene::getCamera() {
    return camera.get();
}

std::vector<std::unique_ptr<Object>> &Scene::getObjects() {
    return objects;
}

const std::vector<LightC *> &Scene::getLights() {
    return lights;
}

void Scene::update(float dt) {
    camera->update();
    for (auto & object : objects){
        object->updatePerFrame(dt);
    }
}

void Scene::addInput(GLFWwindow *window, float dt) {
    camera->getCameraInput(window, dt);
}

void Scene::addObject() {
    std::string name = "Object";
    name += std::to_string(objects.size());
    new Object(this,0,0,0,name);
}

void Scene::addLight(LightC *light) {
    lights.emplace_back(light);
}

ModelManager &Scene::getModelManager() {
    return modelManager;
}
