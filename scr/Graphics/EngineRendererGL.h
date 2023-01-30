#ifndef ENGINE_02_ENGINERENDERERGL_H
#define ENGINE_02_ENGINERENDERERGL_H

#include "EngineRenderer.h"
#include <vector>
#include <algorithm>

class EngineRendererGL : public EngineRenderer{
private:
    ShaderGL shadowMapShader;
public:
    void load() override;

    void loadMesh(Mesh * mesh) override;

    void forwardRender(Scene & scene) override;
    void forwardRenderToShadowMap(Scene & scene) override;

    void drawMesh(Mesh * mesh) override;

    void cleanRenderer() override;
};


#endif //ENGINE_02_ENGINERENDERERGL_H
