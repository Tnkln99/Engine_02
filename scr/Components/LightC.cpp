#include "LightC.h"
#include "ext/matrix_transform.inl"
#include "../Scene.h"

LightC::LightC(Object * owner) : Component("light") {
    setColor(1,1,1);
    intensity = 30.0f;
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
}

void LightC::show(bool condition) {
    if(editModeMesh != nullptr) {
        showSource = condition;
    }
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

const glm::vec3 &LightC::getColor() {
    return color;
}

