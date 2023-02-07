#include <glm/ext/matrix_clip_space.hpp>
#include "LightC.h"
#include "ext/matrix_transform.inl"
#include "../Scene.h"

LightC::LightC() : Component("light") {
    setColor(1,1,1);
    intensity = 30.0f;
    diffuseColor = color * glm::vec3(0.5f);
    ambientColor = color * glm::vec3(0.2f);
}

LightC::~LightC() {

}

void LightC::load(Object *owner) {
    Component::load(owner);
    owner->getScene()->addLight(this);

    Transformable transform = getOwner()->getTransform();

    lightProj = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);
    lightView = glm::lookAt(transform.getPosition(),
                            transform.getPosition() + transform.getDirection(),
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

const glm::vec3 &LightC::getAmbientColor() {
    return ambientColor;
}

const glm::vec3 &LightC::getDiffuseColor() {
    return diffuseColor;
}

const glm::vec3 &LightC::getSpecular() {
    return specular;
}

const glm::mat4 &LightC::getSpaceMatrix() {
    return lightSpaceMatrix;
}


void LightC::updatePositionMessageReceived() {
    Component::updatePositionMessageReceived();
    Transformable transform = getOwner()->getTransform();

    lightView = glm::lookAt(transform.getPosition(),
                            transform.getPosition() + transform.getDirection(),
                            glm::vec3( 0.0f, 1.0f,  0.0f));
    lightSpaceMatrix = lightProj * lightView;
}

Component *LightC::clone() {
    return new LightC(*this);
}








