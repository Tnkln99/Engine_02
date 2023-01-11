#include "Scene.h"
#include "EngineCamera.h"
#include "Components/MeshRendererC.h"
#include "Components/ComponentFactory.h"

void loadComponents(){
    ComponentFactory::Register("Mesh", new MeshC);
    ComponentFactory::Register("MeshRenderer", new MeshRendererC);
    ComponentFactory::Register("Light", new LightC);
}

Scene::Scene() { }

Scene::~Scene(){
    for(auto & mesh : meshes){
        delete mesh;
    }
}

void Scene::load(GLFWwindow * window){
    Assets::loadMaterial(); // todo: this should be else where
    loadComponents();

    camera = std::make_unique<EngineCamera>(window,0,0,10);
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

const std::vector<Mesh*> & Scene::getMeshes() {
    return meshes;
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

void Scene::addMesh(Mesh * mesh) {
    auto it = std::find(meshes.begin(), meshes.end(), mesh);
    if (it == meshes.end()){
        meshes.emplace_back(mesh);
        meshesWaitingToBeLoad.emplace_back(mesh);
    }
}

void Scene::addLight(LightC *light) {
    lights.emplace_back(light);
}

// fins and return if wanted mesh already exists in the scene if it doesn't will return nullptr
Mesh * Scene::findTypeOfMesh(char typeOfMesh) {
    for(auto & mesh : meshes){
        if(mesh->getTypeOfMesh() == typeOfMesh){
            return mesh;
        }
    }
    return nullptr;
}
