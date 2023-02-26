#ifndef ENGINE_02_LIGHTC_H
#define ENGINE_02_LIGHTC_H

#include <glm/glm.hpp>
#include "Component.h"
#include "../../Graphics/BackEnd/ShadowMapFbo.h"
#include "../../Graphics/BackEnd/Model.h"

class Mesh;
class Shader;

class LightC : public Component{
private:
    int shadowTextureWidth = 1619;
    int shadowTextureHeight = 838;

    float intensity{30.0f};

    glm::vec3 color = {1,1,1};
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    glm::mat4 lightProj = glm::mat4(1);
    glm::mat4 lightView = glm::mat4(1);
    glm::mat4 lightSpaceMatrix = glm::mat4(1);
public:
    std::shared_ptr<Model> editModel;
    ShadowMapFbo shadowMap;

    explicit LightC();
    ~LightC() override;

    void load(Object *owner) override;

    void setColor(float r, float g, float b);
    void setIntensity(float intensity);


    [[nodiscard]] float getIntensity() const;
    const glm::vec3 & getColor();
    const glm::mat4 & getSpaceMatrix();

    void positionUpdateMessageReceived() override;

    Component * clone() override;
};


#endif //ENGINE_02_LIGHTC_H

