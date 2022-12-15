#include "Object.h"
#include "Components/RenderComponent.h"
#include "Scene.h"


Object::Object(Scene* owner, float xP, float yP, float zP, std::string name) : owner{owner}, name{std::move(name)}
{
    transform.setPosition(xP, yP, zP);
}

Object::~Object() {

}

void Object::setName(std::string name) {
    this->name = name;
}

void Object::addComponent(Component * sub){
    components.emplace_back(sub);
}

void Object::addRenderComponents(RenderComponent *sub) {
    renderComponents.emplace_back(sub);
}

std::vector<RenderComponent*> & Object::getRenderComponents() {
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

void Object::updateComponents(float dt){
    //std::vector<Component*>::iterator it;
    for (auto & component : components){
        component->update(dt);
    }
}

void Object::update(float dt) {

}


