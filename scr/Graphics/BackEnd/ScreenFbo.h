#ifndef ENGINE_02_SCREENFBO_H
#define ENGINE_02_SCREENFBO_H

#include "FBO.h"

class ScreenFbo : public FBO{
protected:

public:
    void unbind(int width, int height) override;

    void load(int width, int height) override;

    void bind(float r, float g, float b) override;

    void renderToQuad(int width, int height) override;
};


#endif //ENGINE_02_SCREENFBO_H
