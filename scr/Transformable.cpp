#include "Transformable.h"
#include <glm/gtc/matrix_transform.hpp>


const glm::vec3 & Transformable::getPosition() const{
    return position;
}

const glm::mat4 & Transformable::getMoveMatrix() const{
    return mvMatrix;
}

const glm::vec3 & Transformable::getDirection() const{
    return direction;
}

float Transformable::getYaw() const {
    return yaw;
}

float Transformable::getPitch() const {
    return pitch;
}


float Transformable::getRoll() const {
    return roll;
}

void Transformable::setPosition(float x, float y, float z){
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
    mvMatrix = glm::translate(glm::mat4(1), glm::vec3(this->position.x,this->position.y,this->position.z));
}

void Transformable::setPosition(glm::vec3 position){
    this->position.x = position.x;
    this->position.y = position.y;
    this->position.z = position.z;
    mvMatrix = glm::translate(glm::mat4(1), glm::vec3(this->position.x,this->position.y,this->position.z));
}

void Transformable::computeDirection(float yaw, float pitch){
    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;
    
    glm::vec3 tmp;
    tmp.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    tmp.y = sin(glm::radians(pitch));
    tmp.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction = glm::normalize(tmp);
}
