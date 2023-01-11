#ifndef ENGINE_02_ENGINERENDERER_H
#define ENGINE_02_ENGINERENDERER_H

#include <vector>
#include "../Core/Scene.h"

class EngineRenderer {
protected:
    // stores VAO's to delete them later
    std::vector<unsigned int> loadedMeshIds;
public:
    virtual ~EngineRenderer() = default;

    virtual void loadMesh(Mesh * mesh) = 0;

    virtual void forwardRender(Scene & scene) = 0;
    virtual void drawMesh(Mesh * mesh) = 0;

    virtual void cleanRenderer() = 0;
};


#endif //ENGINE_02_ENGINERENDERER_H
