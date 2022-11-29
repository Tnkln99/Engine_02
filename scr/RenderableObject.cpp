#include "RenderableObject.h"

RenderableObject::RenderableObject(float xP, float yP, float zP, Mesh *mesh) : Object(xP, yP, zP, mesh) {
    shininess = 20.0f;

    ambient = glm::vec3(1.0f, 0.5f, 0.31f);
    diffuse = glm::vec3(1.0f, 0.5f, 0.31f);
    specular = glm::vec3(0.5f, 0.5f, 0.5f);
}

float RenderableObject::getShininess() const {
    return shininess;
}
