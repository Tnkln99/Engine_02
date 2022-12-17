#ifndef ENGINE_02_LIGHTC_H
#define ENGINE_02_LIGHTC_H

#include <glm/glm.hpp>
#include "Component.h"

class Mesh;
class Shader;

//TODO complete this class..
class LightC : public Component{
private:
    Mesh* editModeMesh;

    float intensity;
    glm::vec3 color;

    glm::vec3 ambientColor;
    glm::vec3 diffuseColor;
    const glm::vec3 specular = {1,1,1};

    bool showSource = false;
public:
    explicit LightC();
    ~LightC() override;

    void load(Object *owner) override;

    void show(bool condition);
    void setColor(float r, float g, float b);
    void setIntensity(float intensity);


    [[nodiscard]] bool doesShow() const;
    [[nodiscard]] float getIntensity() const;
    const glm::vec3 & getAmbientColor();
    const glm::vec3 & getDiffuseColor();
    const glm::vec3 & getSpecular();

    Mesh * getEditModeMesh();

    Component * clone() override;
};


#endif //ENGINE_02_LIGHTC_H
