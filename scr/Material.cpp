#include "Material.h"

float Material::getShininess() const{
    return shininess;
}

const glm::vec3 & Material::getAmbient() const{
    return ambient;
}

const glm::vec3 & Material::getDiffuse() const{
    return diffuse;
}

const glm::vec3 & Material::getSpecular() const{
    return specular;
}

Shader & Material::getShader() {
    return shader;
}

void Material::setShininess(float shineness){
    this->shininess = shineness;
}

void Material::setAmbient(float x, float y, float z){
    ambient.x = x;
    ambient.y = y;
    ambient.z = z;
}

void Material::setAmbient(glm::vec3 ambient){
    this->ambient.y = ambient.y;
    this->ambient.x = ambient.x;
    this->ambient.z = ambient.z;
}

void Material::setDiffuse(float x, float y, float z){
    diffuse.x = x;
    diffuse.y = y;
    diffuse.z = z;
}

void Material::setDiffuse(glm::vec3 diffuse){
    this->diffuse.y = diffuse.y;
    this->diffuse.x = diffuse.x;
    this->diffuse.z = diffuse.z;
}

void Material::setSpecular(float x, float y, float z) {
    this->specular.y = specular.y;
    this->specular.x = specular.x;
    this->specular.z = specular.z;
}

void Material::setSpecular(glm::vec3 specular) {
    this->specular = specular;
}

void Material::setShader(Shader shader){
    this->shader = shader;
}
