#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>


const glm::vec3 & Transform::getPosition() const{
    return position;
}

const glm::vec3 &Transform::getScale() const {
    return scale;
}

const glm::mat4 & Transform::getModelMatrix() const{
    return modelMatrix;
}

const glm::vec3 & Transform::getDirection() const{
    return direction;
}

float Transform::getYaw() const {
    return yaw;
}

float Transform::getPitch() const {
    return pitch;
}


float Transform::getRoll() const {
    return roll;
}

void Transform::setPosition(float x, float y, float z){
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
    transformMatrix = glm::translate(glm::mat4(1), glm::vec3(this->position.x, this->position.y, this->position.z));
    modelMatrix = transformMatrix * scaleMatrix;
}

void Transform::setPosition(glm::vec3 position){
    this->position.x = position.x;
    this->position.y = position.y;
    this->position.z = position.z;
    transformMatrix = glm::translate(glm::mat4(1), glm::vec3(this->position.x, this->position.y, this->position.z));
    modelMatrix = transformMatrix * scaleMatrix;
}

void Transform::computeDirection(float yaw, float pitch){
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

void Transform::setScale(float x, float y, float z) {
    this->scale = glm::vec3(x,y,z);
    scaleMatrix = glm::scale(glm::mat4(1), this->scale);
    modelMatrix = transformMatrix * scaleMatrix;
}

void Transform::setScale(glm::vec3 scale) {
    this->scale = scale;
    scaleMatrix = glm::scale(modelMatrix, this->scale);
    modelMatrix = transformMatrix * scaleMatrix;
}
