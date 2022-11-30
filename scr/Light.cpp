#include "Light.h"
#include "Shader.h"
#include "Mesh.h"
#include "ext/matrix_transform.inl"

Light::Light(float xP, float yP, float zP, Mesh *mesh) : debugMesh {mesh}, Object(xP, yP, zP) {
    setColor(1,1,1);
}

void Light::show(bool condition) {
    if(debugMesh != nullptr) {
        showSource = condition;
    }
}

void Light::setColor(float r, float g, float b){
    color.r = r;
    color.g = g;
    color.b = b;
}

void Light::setIntensity(float intensity){
    this->intensity = intensity;
}

bool Light::doesShow() const {
    return showSource;
}

float Light::getIntensity() const{
    return intensity;
}

//checking if there is a debugger mesh, for light or not
void Light::draw(Shader &shader, GLenum face) {
    shader.setMatrix4("transform", transform.getMoveMatrix());
    if(debugMesh != nullptr && showSource){
        debugMesh->draw(face);
    }
}


void Light::update() {
    
}
