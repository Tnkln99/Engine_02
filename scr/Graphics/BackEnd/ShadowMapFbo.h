#ifndef ENGINE_02_SHADOWMAPFBO_H
#define ENGINE_02_SHADOWMAPFBO_H

#include "FBO.h"

class ShadowMapFbo : public FBO {
public:
    void load(int width, int height) override;

    void bind(float r, float g, float b) override;

    void unbind(int windowsWidth, int windowsHeight) override;

    void renderToQuad(int width, int height) override;
};


#endif //ENGINE_02_SHADOWMAPFBO_H
