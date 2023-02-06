#include "Component.h"
#include "../Object.h"
#include <iostream>

Component::Component(const std::string & name, int updateOrder){
    this->name = name;
    this->updateOrder = updateOrder;
}

Component::~Component() = default;

void Component::load(Object *owner) {
    this->owner = owner;
    owner->addComponent(this);
}

int Component::getUpdateOrder() const{
    return updateOrder;
}

Object * Component::getOwner(){
    return owner;
}

const std::string & Component::getName(){
    return name;
}

void Component::update(float dt) {

}

void Component::updatePositionMessageReceived(){

}






