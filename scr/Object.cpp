#include "Object.h"
#include "Shader.h"
#include "Mesh.h"

Object::Object(float xP, float yP, Mesh* mesh)
: objectMesh { mesh }
{
    setPosition(xP, yP);
}

void Object::update(double timeSinceStart) {
    const float t = Maths::sin((float)timeSinceStart) * 0.001f;
    Matrix4 rotationY = Matrix4::createRotationY(t * Maths::toRadians(10.0f));
    Matrix4 rotationX = Matrix4::createRotationX(t * Maths::toRadians(10.0f));
    transform *= rotationY;
    transform *= rotationX;
}

void Object::draw(Shader& shader) {
    shader.setMatrix4("transform", transform);
    objectMesh->draw();
}

void Object::setPosition(float xP, float yP) {
  x = xP;
  y = yP;
  transform = computeTransform();
}

Matrix4 Object::computeTransform() const {
  return Matrix4::createTranslation(Vector3(x, y, -6.0f));
}

void Object::clean() {
    objectMesh->clean();
}
