#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include "../../Graphics/Shader.h"

class Material { 
private:
    float shininess {32.0f};

    glm::vec3 ambient{1.0f, 0.5f, 0.31f};
    glm::vec3 diffuse{1.0f, 0.5f, 0.31f};
    glm::vec3 specular{0.5f, 0.5f, 0.5f};

    std::string shaderId;
public:
    Material();

    [[nodiscard]]float getShininess() const;
    [[nodiscard]] const glm::vec3 & getAmbient() const;
    [[nodiscard]] const glm::vec3 & getDiffuse() const;
    [[nodiscard]] const glm::vec3 & getSpecular() const;

    [[nodiscard]] const std::string & getShaderId() const;

    void setShaderId(const std::string & shaderId);

    void setShininess(float shininess);
    
    void setAmbient(float x, float y, float z);
    void setAmbient(glm::vec3 ambient);
    
    void setDiffuse(float x, float y, float z);
    void setDiffuse(glm::vec3 diffuse);
    
    void setSpecular(float x, float y, float z);
    void setSpecular(glm::vec3 specular);
};

#endif