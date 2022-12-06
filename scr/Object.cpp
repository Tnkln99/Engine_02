#include "Object.h"
#include "RenderComponent.h"
#include "Scene.h"


Object::Object(Scene * owner, float xP, float yP, float zP, std::string name) : owner{owner}, name{std::move(name)}
{
    transform.setPosition(xP, yP, zP);
    owner->addObject(this);
}

void Object::addComponent(Component * sub){
    components.emplace_back(sub);
    std::vector<Component*>::iterator it;
    for(it = components.begin(); it != components.end(); it++) {
        (*it)->onComponentAdd();
    }
}

void Object::addRenderComponents(RenderComponent *sub) {
    renderComponents.emplace_back(sub);
}

Component * Object::findComponentByName(const std::string & nameComponent){
    std::vector<Component*>::iterator it;
    for(it = components.begin(); it != components.end(); it++) {
        if((*it)->getName() == nameComponent){
            return (*it);
        }
    }
    return nullptr;
}

std::vector<RenderComponent*> & Object::getRenderComponents() {
    return renderComponents;
}

void Object::updateComponents(float dt){
    std::vector<Component*>::iterator it;
    for(it = components.begin(); it != components.end(); it++) {
        (*it)->update(dt);
    }
}

void Object::update(float dt) {

}






