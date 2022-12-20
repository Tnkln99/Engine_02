#ifndef ENGINE_02_FRAMEBUFFER_H
#define ENGINE_02_FRAMEBUFFER_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"


class Framebuffer {
private:
    int textureWidth = 800;
    int textureHeight = 800;

    Shader screenShader;

    unsigned int quadVAO;

    unsigned int fbo;
    unsigned int texture;
    unsigned int rbo;
public:
    void load();

    [[nodiscard]]int getTexture() const;

    // binds to framebuffer and enables depth
    void bind();

    // unbinds from frame buffer and draws everything to texture
    void renderToTexture();
};


#endif //ENGINE_02_FRAMEBUFFER_H
