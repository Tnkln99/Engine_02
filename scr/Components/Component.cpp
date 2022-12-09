#include "Component.h"
#include "../Object.h"

Component::Component(const std::string & name, int updateOrder){
    this->name = name;
    this->updateOrder = updateOrder;
}

void Component::load(Object *owner) {
    this->owner = owner;
    owner->addComponent(this);
}

Component::~Component() = default;

int Component::getUpdateOrder() const{
    return updateOrder;
}

const Object * Component::getOwner(){
    return owner;
}

const std::string & Component::getName(){
    return name;
}

void Component::update(float dt) {

}






