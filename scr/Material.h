#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

class Material { 
private:
    float shininess;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

public:
    Material();
 
    [[nodiscard]]float getShininess() const;
    const glm::vec3 & getAmbient() const;
    const glm::vec3 & getDiffuse() const;
    const glm::vec3 & getSpecular() const;

    void setShininess(float shininess);
    
    void setAmbient(float x, float y, float z);
    void setAmbient(glm::vec3 ambient);
    
    void setDiffuse(float x, float y, float z);
    void setDiffuse(glm::vec3 diffuse);
    
    void setSpecular(float x, float y, float z);
    void setSpecular(glm::vec3 specular);
};

#endif