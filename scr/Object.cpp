#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include "Mesh.h"


Object::Object(float xP, float yP, float zP, Mesh* mesh)
: objectMesh { mesh }
{
    setPosition(xP, yP, zP);
}

void Object::update() {
    transform = glm::rotate(transform, 3.0f * glm::radians(0.05f) * glm::radians(10.0f), glm::vec3(0.5f, 1.0f, 0.0f));
}

void Object::draw(Shader& shader, GLenum face) {
    shader.setMatrix4("transform", transform);
    objectMesh->draw(face);
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
