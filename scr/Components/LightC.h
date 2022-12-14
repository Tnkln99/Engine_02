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

    bool showSource = false;
public:
    explicit LightC(Object * owner);
    ~LightC() override;

    void show(bool condition);
    void setColor(float r, float g, float b);
    void setIntensity(float intensity);


    [[nodiscard]] bool doesShow() const;
    [[nodiscard]] float getIntensity() const;
    const glm::vec3 & getColor();

    void load(Object *owner) override;
};


#endif //ENGINE_02_LIGHTC_H
