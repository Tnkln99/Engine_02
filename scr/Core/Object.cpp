#include "Object.h"
#include "Scene.h"


Object::Object(Scene* owner, float xP, float yP, float zP, std::string name) : owner{owner}, name{std::move(name)}
{
    transform.setPosition(xP, yP, zP);
    owner->addObject(this);
}

Object::~Object() {
    for(auto & component : components){
        delete component;
    }
    components.clear();
}

void Object::setName(std::string name) {
    this->name = name;
}

void Object::addComponent(Component * sub){
    components.emplace_back(sub);
}

void Object::addRenderComponents(MeshRendererC *sub) {
    renderComponents.emplace_back(sub);
}

std::vector<MeshRendererC*> & Object::getRenderComponents() {
    return renderComponents;
}

std::vector<Component*> &Object::getComponents() {
    return components;
}

const std::string &Object::getName() {
    return name;
}

Transformable &Object::getTransform() {
    return transform;
}


Scene * Object::getScene() {
    return owner;
}

void Object::updatePerFrame(float dt){
    for (auto & component : components){
        component->update(dt);
    }
}

void Object::updatePositionMessageSent() {
    for (auto & component : components){
        component->updatePositionMessageReceived();
    }
}


