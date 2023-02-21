#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include <string>
#include "Shader.h"
#include <vector>

struct Texture{
    unsigned int id;
    std::string type;
    std::string path;
};

class Material { 
private:
    // todo: increasing this decrease shine of the object (toFix)
    float shininess {32.0f};

    glm::vec3 ambient{0,0,0};
    glm::vec3 diffuse{0.8,0.8,0.8};
    glm::vec3 specular{1,1,1};

    std::string shaderId;
    std::string textureId = " ";
public:
    Shader * shader;
    std::vector<Texture> textures;

    explicit Material(Shader * shaderToUse);

    [[nodiscard]]float getShininess() const;
    [[nodiscard]] const glm::vec3 & getAmbient() const;
    [[nodiscard]] const glm::vec3 & getDiffuse() const;
    [[nodiscard]] const glm::vec3 & getSpecular() const;

    [[nodiscard]] const std::string & getShaderId() const;
    [[nodiscard]] const std::string & getTextureId() const;

    void setShaderId(const std::string & shaderId);
    void setTextureId(const std::string & textureId);

    void setShininess(float shininess);
    
    void setAmbient(float x, float y, float z);
    void setAmbient(glm::vec3 ambient);
    
    void setDiffuse(float x, float y, float z);
    void setDiffuse(glm::vec3 diffuse);
    
    void setSpecular(float x, float y, float z);
    void setSpecular(glm::vec3 specular);
};

#endif