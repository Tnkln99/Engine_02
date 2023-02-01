#ifndef ENGINE_02_SCREENFBO_H
#define ENGINE_02_SCREENFBO_H

#include "FBO.h"

class ScreenFbo : public FBO {
public:
    void unbind(int width, int height) override;

    void load(int width, int height) override;

    [[nodiscard]] int getTextureWidth() const override;

    [[nodiscard]] int getTextureHeight() const override;

    [[nodiscard]] unsigned int getTexture() const override;

    void bind() override;

};


#endif //ENGINE_02_SCREENFBO_H
