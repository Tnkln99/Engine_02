#ifndef CUBEOBJECT_H
#define CUBEOBJECT_H

#include "../lib/maths/Matrix4.h"
#include <ctime>
#define _USE_MATH_DEFINES
#include <cmath>


class Shader;
class Mesh;

class Object {
private:
    float x { 0.0f };
    float y { 0.0f };
    Matrix4 transform {};

    Mesh* cubeMesh;
public:
  Object(float xP, float yP, Mesh* cubeMeshP);

  void update(double timeSinceStart);
  void draw(Shader& shader);

  [[nodiscard]] float getX() const { return x; }
  [[nodiscard]] float getY() const { return y; }
  void setPosition(float xP, float yP);
  [[nodiscard]] Matrix4 computeTransform() const;

  void clean();
};

#endif