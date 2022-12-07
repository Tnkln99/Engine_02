#include "RenderComponent.h"
#include "Object.h"

RenderComponent::RenderComponent(Object * owner, const std::string & name, int updateOrder) : Component(owner, name, updateOrder) {
    owner->addRenderComponents(this);
}
