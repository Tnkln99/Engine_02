#ifndef ENGINE_02_LIGHT_H
#define ENGINE_02_LIGHT_H

#include <glm/glm.hpp>
#include "Object.h"

class Mesh;
class Shader;

//TODO complete this class..
class Light : public Object{
private:
    Mesh* mesh;

    bool showSource = false;
    float intensity;
    glm::vec3 color;
public:
    Light(float xP, float yP, float zP, Mesh* mesh = nullptr);

    void show(bool condition);
    void setColor(float r, float g, float b);
    void setIntensity(float intensity);


    [[nodiscard]] bool doesShow() const;
    [[nodiscard]] float getIntensity() const;
    const glm::vec3 & getColor();

    void draw(Shader& shader, GLenum face);

        virtual void update();
};


#endif //ENGINE_02_LIGHT_H
