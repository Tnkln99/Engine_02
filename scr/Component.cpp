#include "Component.h"
#include "Object.h"

Component::Component(Object * owner, const std::string & name, int updateOrder): owner{owner}{
    this->name = name;
    this->updateOrder = updateOrder;
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


