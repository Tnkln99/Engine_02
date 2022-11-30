#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"


Object::Object(float xP, float yP, float zP)
{
    transform.setPosition(xP, yP, zP);
}

const Transformable & Object::getTransform(){
    return transform;
}
