#ifndef ENGINE_02_FBO_H
#define ENGINE_02_FBO_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include <vector>


class FBO {
protected:
    Shader debugShader;
    unsigned int quadVAO{};

    int textureWidth{};
    int textureHeight{};

    unsigned int fbo{};
    unsigned int texture{};
    unsigned int rbo{};
public:
    void loadQuad(){
        float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
                // positions            // texCoords
                -1.0f,  1.0f,  0.0f, 1.0f,
                -1.0f, -1.0f,  0.0f, 0.0f,
                1.0f, -1.0f,  1.0f, 0.0f,

                -1.0f,  1.0f,  0.0f, 1.0f,
                1.0f, -1.0f,  1.0f, 0.0f,
                1.0f,  1.0f,  1.0f, 1.0f
        };
        unsigned int quadVBO;
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    };

    virtual void load(int width, int height){
        this->textureWidth = width;
        this->textureHeight = height;

        loadQuad();
    };

    [[nodiscard]] virtual int getTextureWidth() const {
        return textureWidth;
    };

    [[nodiscard]] virtual int getTextureHeight() const {
        return textureHeight;
    };

    [[nodiscard]] virtual unsigned int getTexture() const {
        return texture;
    };

    virtual void bind(float r, float g, float b) = 0;

    virtual void unbind(int windowsWidth, int windowsHeight) = 0;

    // for debug purposes it will render the fbo to the screen
    // should be overriden to attach to the debug shader and pass the uniforms
    virtual void renderToQuad(int width, int height){
        glViewport(0,0,width,height);
        glBindVertexArray(quadVAO);
        glBindTexture(GL_TEXTURE_2D, texture);	// use the color attachment texture as the texture of the quad plane
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    };
};


#endif //ENGINE_02_FBO_H
