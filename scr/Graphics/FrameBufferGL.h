#ifndef ENGINE_02_FRAMEBUFFERGL_H
#define ENGINE_02_FRAMEBUFFERGL_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "ShaderGL.h"


class FrameBufferGL {
private:
    int textureWidth;
    int textureHeight;

    unsigned int fbo;
    unsigned int texture;
    unsigned int rbo;
public:
    void load();

    [[nodiscard]]unsigned int getTexture() const;
    [[nodiscard]]int getTextureWidth() const;
    [[nodiscard]]int getTextureHeight() const;

    // binds to screenFbo and enables depth
    void bind();

    // unbinds from frame buffer and draws everything to texture
    void unbind(int windowsWidth, int windowsHeight);
};


#endif //ENGINE_02_FRAMEBUFFERGL_H
