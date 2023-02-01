#include "Scene.h"
#include "EngineCamera.h"
#include "Components/ComponentFactory.h"

void loadComponents(){
    ComponentFactory::Register("Mesh", new MeshC);
    ComponentFactory::Register("MeshRenderer", new MeshRendererC);
    ComponentFactory::Register("Light", new LightC);
}

Scene::Scene() { }

Scene::~Scene() { }

void Scene::load(GLFWwindow * window, float sceneWidth, float sceneHeight){
    loadComponents();

    camera = std::make_unique<EngineCamera>(window, sceneWidth, sceneHeight, 0,0,10);
}

EngineCamera *Scene::getCamera() {
    return camera.get();
}

const std::vector<std::unique_ptr<Object>> &Scene::getObjects() {
    return objects;
}

const std::vector<LightC *> &Scene::getLights() {
    return lights;
}


std::vector<Mesh*> & Scene::getMeshesWTBL() {
    return meshesWaitingToBeLoad;
}

void Scene::update(float dt) {
    camera->update();
    for (auto & object : objects){
        object->updateComponents(dt);
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

void Scene::addMesh(std::shared_ptr<Mesh> mesh) {
    meshesWaitingToBeLoad.emplace_back(mesh.get());
}

void Scene::addLight(LightC *light) {
    lights.emplace_back(light);
}

std::shared_ptr<Mesh> Scene::findMesh(char typeOfMesh) {
    for(auto & object : objects){
        for(auto & renderC : object->getRenderComponents()){
            if (renderC->getMeshC()->getMesh() == nullptr){return nullptr;}
            if(renderC->getMeshC()->getMesh()->getTypeOfMesh() == typeOfMesh){
                return renderC->getMeshC()->getMesh();
            }
        }
    }
    return nullptr;
}
