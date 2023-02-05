#include "ScreenFbo.h"
#include "../../Utils/Assets.h"


void ScreenFbo::load(int width, int height) {
    FBO::load(width, height);
    debugShader = Assets::loadShaderFromFile("../assets/shaders/debug/screenDebug.vert", "../assets/shaders/debug/screenDebug.frag", "", "", "");

    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    // create a color attachment texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, textureWidth, textureHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, textureWidth, textureHeight); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
    // now that we actually created the screenFbo and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: FBO is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    debugShader.use();
    debugShader.setInteger("screenTexture", 0);
}


void ScreenFbo::bind(float r, float g, float b) {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
    glViewport(0,0,textureWidth,textureHeight);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ScreenFbo::unbind(int windowsWidth, int windowsHeight) {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    // clear all relevant buffers
    glClearColor(0, 0, 0, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
}

void ScreenFbo::renderToQuad(int width, int height) {
    debugShader.use();
    FBO::renderToQuad(width, height);
}


