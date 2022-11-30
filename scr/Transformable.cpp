#include "Transformable.h"


const glm::vec3 & Transformable::getPosition() const{
    return position;
}

const glm::mat4 & Transformable::getMoveMatrix() const{
    return mvMatrix;
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
    position.x = x;
    position.y = y;
    position.z = z;
    mvMatrix = glm::translate(mvMatrix, glm::vec3(this->position.x,this->position.y,this->position.z));
}

void Transformable::setPosition(glm::vec3 position){
    this->position.x = position.x;
    this->position.y = position.y;
    this->position.z = position.z;
    mvMatrix = glm::translate(mvMatrix, glm::vec3(this->position.x,this->position.y,this->position.z));
}

void Transformable::setYaw(float yaw){
    this->yaw = yaw;
    computeDirection();
}

void Transformable::setPitch(float pitch){
    this->pitch = pitch;
    computeDirection();
}

void Transformable::setRoll(float roll){
    this->roll = roll;
    computeDirection();
}

void Transformable::computeDirection(){
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction = glm::normalize(direction);
}
