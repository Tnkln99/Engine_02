#ifndef ENGINE_02_FRAMEBUFFERGL_H
#define ENGINE_02_FRAMEBUFFERGL_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "ShaderGL.h"


class FrameBufferGL {
private:
    int textureWidth = 1652;
    int textureHeight = 1042;

    unsigned int quadVAO;

    unsigned int fbo;
    unsigned int texture;
    unsigned int rbo;
public:
    void load();

    [[nodiscard]]int getTexture() const;
    [[nodiscard]]int getTextureWidth() const;
    [[nodiscard]]int getTextureHeight() const;

    // binds to framebuffer and enables depth
    void bind();

    // unbinds from frame buffer and draws everything to texture
    void renderTexture(int windowsWidth, int windowsHeight);
};


#endif //ENGINE_02_FRAMEBUFFERGL_H
