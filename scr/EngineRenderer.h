#ifndef ENGINE_02_ENGINERENDERER_H
#define ENGINE_02_ENGINERENDERER_H

#include <vector>
#include "Scene.h"

class EngineRenderer {
protected:
    std::vector<unsigned int*> loadedMeshIds;
public:
    virtual ~EngineRenderer() = default;

    virtual void loadMesh(Mesh * mesh) = 0;

    virtual void drawAll(Scene & scene) = 0;
    virtual void drawMesh(Mesh * mesh) = 0;

    virtual void cleanRenderer() = 0;
};


#endif //ENGINE_02_ENGINERENDERER_H
