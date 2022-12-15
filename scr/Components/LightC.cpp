#include "LightC.h"
#include "ext/matrix_transform.inl"
#include "../Scene.h"

LightC::LightC() : Component("light") {
    setColor(1,1,1);
    intensity = 30.0f;
    diffuseColor = color * glm::vec3(0.5f);
    ambientColor = color * glm::vec3(0.2f);
    editModeMesh = nullptr;
}

LightC::~LightC() {
    delete editModeMesh;
}

void LightC::load(Object *owner) {
    Component::load(owner);
    if(owner->getScene()->findTypeOfMesh('s') != nullptr){
        editModeMesh = owner->getScene()->findTypeOfMesh('s');
    }
    else {
        editModeMesh = new Mesh;
    }
    owner->getScene()->addMesh(editModeMesh);
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

Mesh *LightC::getEditModeMesh() {
    return editModeMesh;
}

Component *LightC::clone() {
    return new LightC(*this);
}





