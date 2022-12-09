#ifndef ENGINE_02_ENGINERENDERERGL_H
#define ENGINE_02_ENGINERENDERERGL_H

#include "EngineRenderer.h"
#include <vector>
#include <algorithm>

class EngineRendererGL : public EngineRenderer{
public:
    void loadMesh(Mesh * mesh) override;

    void drawAll(Scene & scene) override;
    void drawMesh(Mesh * mesh) override;

    void cleanRenderer() override;
};


#endif //ENGINE_02_ENGINERENDERERGL_H
