#ifndef ENGINE_02_RENDERABLEOBJECT_H
#define ENGINE_02_RENDERABLEOBJECT_H
#include "Object.h"

class RenderableObject : public Object{
private:
    float shininess;
public:
    RenderableObject(float xP, float yP, float zP, Mesh *mesh);

    [[nodiscard]] float getShininess() const ;
};


#endif //ENGINE_02_RENDERABLEOBJECT_H
