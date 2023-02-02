#ifndef ENGINE_02_SHADOWMAPFBO_H
#define ENGINE_02_SHADOWMAPFBO_H

#include "FBO.h"

class ShadowMapFbo : public FBO {
public:
    void load(int width, int qheight) override;

    [[nodiscard]] int getTextureWidth() const override;

    [[nodiscard]] int getTextureHeight() const override;

    [[nodiscard]] unsigned int getTexture() const override;

    void bind() override;

    void unbind(int windowsWidth, int windowsHeight) override;

};


#endif //ENGINE_02_SHADOWMAPFBO_H
