#ifndef ENGINE_02_LIGHT_H
#define ENGINE_02_LIGHT_H

#include <glm/glm.hpp>
#include "Object.h"

//TODO complete this class..
class Light : public Object{
private:
    bool showSource = false;
public:
    Light(float xP, float yP, float zP, Mesh* mesh = nullptr);

    void show(bool condition);
    [[nodiscard]] bool doesShow() const;

    void update() override;
    void draw(Shader& shader, GLenum face) override;
};


#endif //ENGINE_02_LIGHT_H
