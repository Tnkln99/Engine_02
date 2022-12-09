#include "Scene.h"
#include "EngineCamera.h"
#include "Components/MeshRenderer.h"
#include "Components/ComponentFactory.h"

void loadComponents(){
    ComponentFactory::Register("Mesh", new Mesh);
    ComponentFactory::Register("MeshRenderer", new MeshRenderer);
}

Scene::Scene() { }

Scene::~Scene(){

}

EngineCamera *Scene::getCamera() {
    return camera;
}

const std::vector<Object *> &Scene::getObjects() {
    return objects;
}

const std::vector<Mesh *> &Scene::getMeshes() {
    return meshes;
}

void Scene::load(GLFWwindow * window){
    Assets::loadMaterial("../shaders/default.vert", "../shaders/default.frag", "", "", "", "Default");
    loadComponents();

    camera = new EngineCamera(window);
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
    new Object{this,0.0f,0,-10.0f, name};
    /*if(findTypeOfMesh('s') != nullptr){
        newObject->addComponent(findTypeOfMesh('s'));
    }
    else{
        new Mesh{newObject, 's'};
    }
    new MeshRenderer{newObject};*/
}

void Scene::addMesh(Mesh * mesh) {
    meshes.emplace_back(mesh);
}

// fins and return if wanted mesh already exists in the scene if it doesn't will return nullptr
Mesh *Scene::findTypeOfMesh(char typeOfMesh) {
    for (auto & mesh : meshes){
        if (mesh->getTypeOfMesh() == typeOfMesh){
            return mesh;
        }
    }
    return nullptr;
}






