#ifndef CUBEOBJECT_H
#define CUBEOBJECT_H

#include <ctime>
#define _USE_MATH_DEFINES
#include <cmath>
#include <glm/glm.hpp>


class Shader;
class Mesh;

class Object {
private:
    float x { 0.0f };
    float y { 0.0f };
    float z { 0.0f };
    glm::mat4 transform = glm::mat4(1.0f);

    Mesh* objectMesh;
public:
  Object(float xP, float yP, float zP, Mesh* mesh);

  void update();
  void draw(Shader& shader);

  [[nodiscard]] float getX() const { return x; }
  [[nodiscard]] float getY() const { return y; }
  void setPosition(float xP, float yP, float zP);

  void clean();
};

#endif