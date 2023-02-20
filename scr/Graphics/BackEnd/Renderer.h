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
    // stores VAO's to delete them later
    std::vector<unsigned int> loadedMeshIds;
    RenderMode renderMode = RenderMode::FILL;

    Shader shadowMapShader;
    Shader debugNormals;
    unsigned int shadowMapTexture;

    SkyBoxCubeMap skyBox;
public:
    void load();

    void loadMesh(Mesh * mesh);

    void renderToShadowMap(Scene & scene);
    void renderScene(Scene & scene, unsigned int depthMap);

    void drawMesh(Mesh * mesh);

    void setRenderMode(int mode);

    void cleanRenderer();
};


#endif //ENGINE_02_RENDERER_H
