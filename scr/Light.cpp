#include "Light.h"
#include "Shader.h"
#include "Mesh.h"
#include "ext/matrix_transform.inl"

Light::Light(float xP, float yP, float zP, Mesh *mesh) : Object(xP, yP, zP, mesh) {
    setColor(1,1,1);

    ambient = glm::vec3(0.2f, 0.2f, 0.2f);
    diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    specular = glm::vec3(1.0f, 1.0f, 1.0f);

    transform = glm::scale(transform, glm::vec3(0.2f));
}

void Light::update() {
    
}

//checking if there is a debugger mesh, for light or not
void Light::draw(Shader &shader, GLenum face) {
    shader.setMatrix4("transform", transform);
    if(objectMesh != nullptr && showSource){
        objectMesh->draw(face);
    }
}

void Light::show(bool condition) {
    if(objectMesh != nullptr) {
        showSource = condition;
    }
}

bool Light::doesShow() const {
    return showSource;
}
