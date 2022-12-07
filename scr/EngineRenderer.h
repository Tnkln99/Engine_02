#ifndef ENGINE_02_ENGINERENDERER_H
#define ENGINE_02_ENGINERENDERER_H

#include <vector>
#include "Scene.h"

class EngineRenderer {
protected:
    std::vector<Component*> renderComponent;
    std::vector<unsigned int*> loadedMeshIds;
public:
    virtual ~EngineRenderer() = default;

    void addRenderComponent(Component* component){
        renderComponent.emplace_back(component);
    };

    virtual void loadMesh(Mesh * mesh) = 0;

    virtual void drawAll(const Scene & scene) = 0;
    virtual void drawMesh(Mesh * mesh) = 0;

    virtual void cleanRenderer() = 0;
};


#endif //ENGINE_02_ENGINERENDERER_H
