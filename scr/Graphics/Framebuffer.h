#ifndef ENGINE_02_FRAMEBUFFER_H
#define ENGINE_02_FRAMEBUFFER_H

#include <glad/glad.h>


class Framebuffer {
private:
    int bufferWith = 600;
    int bufferHeight = 600;

    unsigned int quadVAO;

    unsigned int fbo;
    unsigned int texture;
    unsigned int rbo;
public:
    Framebuffer();
    ~Framebuffer();

    void renderToBuffer() const;
};


#endif //ENGINE_02_FRAMEBUFFER_H
