#ifndef ENGINE_02_RENDERCOMPONENT_H
#define ENGINE_02_RENDERCOMPONENT_H

#include "Component.h"
#include "../Material.h"

class Object;
class MeshC;

class RenderComponent : public Component{
private:
public:
    explicit RenderComponent(const std::string & name, int updateOrder = 100);

    RenderComponent();

    virtual Material & getMaterial() = 0;
    virtual MeshC * getMeshC() = 0;
};


#endif //ENGINE_02_RENDERCOMPONENT_H
