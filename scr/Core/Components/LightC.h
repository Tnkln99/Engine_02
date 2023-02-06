#ifndef ENGINE_02_LIGHTC_H
#define ENGINE_02_LIGHTC_H

#include <glm/glm.hpp>
#include "Component.h"

class Mesh;
class Shader;

// todo: complete this class..
class LightC : public Component{
private:
    float intensity;
    glm::vec3 color;

    glm::vec3 ambientColor;
    glm::vec3 diffuseColor;
    const glm::vec3 specular = {1,1,1};

    float nearPlane = 1.0f;
    float farPlane = 20.0f;

    glm::mat4 lightProj = glm::mat4(1);
    glm::mat4 lightView = glm::mat4(1);
    glm::mat4 lightSpaceMatrix = glm::mat4(1);
public:
    explicit LightC();
    ~LightC() override;

    void load(Object *owner) override;

    void setColor(float r, float g, float b);
    void setIntensity(float intensity);


    [[nodiscard]] float getIntensity() const;
    const glm::vec3 & getAmbientColor();
    const glm::vec3 & getDiffuseColor();
    const glm::vec3 & getSpecular();
    const glm::mat4 & getSpaceMatrix();

    void updatePositionMessageReceived() override;

    Component * clone() override;
};


#endif //ENGINE_02_LIGHTC_H

