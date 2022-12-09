#include "RenderComponent.h"
#include "../Object.h"

RenderComponent::RenderComponent(const std::string & name, int updateOrder) : Component( name, updateOrder) { }

RenderComponent::RenderComponent() = default;
