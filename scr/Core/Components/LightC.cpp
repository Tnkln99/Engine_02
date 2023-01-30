#include <glm/ext/matrix_clip_space.hpp>
#include "LightC.h"
#include "ext/matrix_transform.inl"
#include "../Scene.h"

LightC::LightC() : Component("light") {
    setColor(1,1,1);
    intensity = 30.0f;
    diffuseColor = color * glm::vec3(0.5f);
    ambientColor = color * glm::vec3(0.2f);

    lightProj = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);
    lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
                            glm::vec3( 0.0f, 0.0f,  0.0f),
                            glm::vec3( 0.0f, 1.0f,  0.0f));
    lightSpaceMatrix = lightProj * lightView;
}

LightC::~LightC() {

}

void LightC::load(Object *owner) {
    Component::load(owner);
    /*if(owner->getScene()->findMesh('t') != nullptr){
        editModeMesh = owner->getScene()->findMesh('t');
    }
    else {
        editModeMesh = new Mesh('t');
    }
    owner->getScene()->addMesh(editModeMesh);*/
    owner->getScene()->addLight(this);
}

void LightC::show(bool condition) {
    showSource = condition;
}

void LightC::setColor(float r, float g, float b){
    color.r = r;
    color.g = g;
    color.b = b;
}

void LightC::setIntensity(float intensity){
    this->intensity = intensity;
}

bool LightC::doesShow() const {
    return showSource;
}

float LightC::getIntensity() const{
    return intensity;
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

Component *LightC::clone() {
    return new LightC(*this);
}






