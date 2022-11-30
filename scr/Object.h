#ifndef OBJECT_H
#define OBJECT_H

#include "Transformable.h"

#include <ctime>
#define _USE_MATH_DEFINES
#include <glad/glad.h>
#include <cmath>
#include <glm/glm.hpp>

class Object {
private:
  Transformable transform;  
public:
  Object(float xP, float yP, float zP);

  const Transformable & getTransform();
};

#endif