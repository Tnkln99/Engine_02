#ifndef ENGINE_02_RENDERABLEOBJECT_H
#define ENGINE_02_RENDERABLEOBJECT_H

#include "Object.h"
#include "Material.h"
#include <ctime>

class Mesh;
class Shader;

class RenderableObject : public Object{
private:
    Material material;
    Mesh* mesh;
public:
    RenderableObject(float xP, float yP, float zP, Mesh *mesh);

    void draw(Shader& shader, GLenum face);

    void clean();
};


#endif //ENGINE_02_RENDERABLEOBJECT_H
