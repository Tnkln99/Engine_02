#ifndef ENGINE_02_FBO_H
#define ENGINE_02_FBO_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"


class FBO {
protected:
    int textureWidth{};
    int textureHeight{};

    unsigned int fbo{};
    unsigned int texture{};
    unsigned int rbo{};
public:
    virtual void load(int width, int height) = 0;

    [[nodiscard]] virtual int getTextureWidth() const = 0;
    [[nodiscard]] virtual int getTextureHeight() const = 0;
    [[nodiscard]] virtual unsigned int getTexture() const = 0;

    virtual void bind() = 0;

    virtual void unbind(int windowsWidth, int windowsHeight) = 0;
};


#endif //ENGINE_02_FBO_H
