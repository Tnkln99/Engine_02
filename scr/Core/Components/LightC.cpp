#include <glm/ext/matrix_clip_space.hpp>
#include "LightC.h"
#include "ext/matrix_transform.inl"
#include "../Scene.h"

LightC::LightC() : Component("light") {

}

LightC::~LightC() = default;

void LightC::load(Object *owner) {
    Component::load(owner);
    owner->getScene()->addLight(this);

    Transformable transform = getOwner()->getTransform();

    lightProj = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);
    lightView = glm::lookAt(transform.getPosition(),
                            glm::vec3(0,0,0),
                            glm::vec3( 0.0f, 1.0f,  0.0f));
    lightSpaceMatrix = lightProj * lightView;
}


void LightC::setColor(float r, float g, float b){
    color.r = r;
    color.g = g;
    color.b = b;
}

void LightC::setIntensity(float intensity){
    this->intensity = intensity;
}

float LightC::getIntensity() const{
    return intensity;
}


const glm::vec3 &LightC::getColor() {
    return color;
}

const glm::mat4 &LightC::getSpaceMatrix() {
    return lightSpaceMatrix;
}


void LightC::updatePositionMessageReceived() {
    Component::updatePositionMessageReceived();

    lightView = glm::lookAt(getOwner()->getTransform().getPosition(),
                            glm::vec3(0,0,0), // where it looks
                            glm::vec3( 0.0f, 1.0f,  0.0f));
    lightSpaceMatrix = lightProj * lightView;
}

Component *LightC::clone() {
    return new LightC(*this);
}








