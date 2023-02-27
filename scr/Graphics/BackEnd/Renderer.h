#ifndef ENGINE_02_RENDERER_H
#define ENGINE_02_RENDERER_H

#include <algorithm>
#include <vector>
#include "../../Core/Scene.h"
#include "Shader.h"
#include "SkyBoxCubeMap.h"

class Renderer{
private:
    enum RenderMode{
        FILL,
        POINT,
        LINE
    };
    RenderMode renderMode = RenderMode::FILL;

    Shader shadowMapShader;
    Shader normalsShader;
    Shader lightsShader;

    SkyBoxCubeMap skyBox;
public:
    void load();

    void renderToShadowMap(Scene & scene);
    void renderScene(Scene & scene, unsigned int depthMap);

    void drawMesh(Mesh * mesh);

    void setRenderMode(int mode);
};


#endif //ENGINE_02_RENDERER_H
