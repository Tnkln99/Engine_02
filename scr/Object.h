#ifndef CUBEOBJECT_H
#define CUBEOBJECT_H

#include <ctime>
#define _USE_MATH_DEFINES
#include <glad/glad.h>
#include <cmath>
#include <glm/glm.hpp>


class Shader;
class Mesh;

class Object {
private:
    float x { 0.0f };
    float y { 0.0f };
    float z { 0.0f };
protected:
    glm::mat4 transform = glm::mat4(1.0f);
    Mesh* objectMesh;

    glm::vec3 color;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
public:
  Object(float xP, float yP, float zP, Mesh* mesh);

  virtual void update();
  virtual void draw(Shader& shader, GLenum face);

  [[nodiscard]] float getX() const { return x; }
  [[nodiscard]] float getY() const { return y; }
  [[nodiscard]] float getZ() const { return z; }
  [[nodiscard]] const glm::vec3 & getColor();

  [[nodiscard]] glm::vec3 getPosition() const;
  [[nodiscard]] glm::vec3 getAmbient() const;
  [[nodiscard]] glm::vec3 getDiffuse() const;
  [[nodiscard]] glm::vec3 getSpecular() const;

  void setPosition(float xP, float yP, float zP);
  void setColor(float r, float g, float b);

  void clean();
};

#endif