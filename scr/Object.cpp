#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include "Mesh.h"


Object::Object(float xP, float yP, float zP, Mesh* mesh)
: objectMesh { mesh }
{
    setColor(0,0,0.1);
    setPosition(xP, yP, zP);
}

//TODO
void Object::update() {
    transform = glm::rotate(transform, 3.0f * glm::radians(0.05f) * glm::radians(10.0f), glm::vec3(0.5f, 1.0f, 0.0f));
}

void Object::draw(Shader& shader, GLenum face) {
    shader.setMatrix4("transform", transform);
    objectMesh->draw(face);
}

const glm::vec3 &Object::getColor() {
    return color;
}

glm::vec3 Object::getAmbient() const {
    return ambient;
}

glm::vec3 Object::getDiffuse() const {
    return diffuse;
}

glm::vec3 Object::getSpecular() const {
    return specular;
}

glm::vec3 Object::getPosition() const {
    glm::vec3 pos {x,y,z};
    return pos;
}

void Object::setPosition(float xP, float yP, float zP) {
  x = xP;
  y = yP;
  z = zP;
  transform = glm::translate(transform, glm::vec3(x,y,z));
}

void Object::clean() {
    objectMesh->clean();
}

void Object::setColor(float r, float g, float b) {
    color.r = r;
    color.g = g;
    color.b = b;
}
