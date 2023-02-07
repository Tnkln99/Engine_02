#include "ShadowMapFbo.h"
#include "Assets.h"

void ShadowMapFbo::load(int width, int height) {
    FBO::load(width, height);
    debugShader = Assets::loadShaderFromFile("../assets/shaders/debug/shadowMapDebug.vert", "../assets/shaders/debug/shadowMapDebug.frag", "", "", "");

    glGenFramebuffers(1, &fbo);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, textureWidth, textureHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    debugShader.use();
    debugShader.setInteger("depthMap", 0);
}

void ShadowMapFbo::bind(float r, float g, float b) {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
    glViewport(0,0,textureWidth,textureHeight);
    glEnable(GL_DEPTH_TEST);
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ShadowMapFbo::unbind(int windowsWidth, int windowsHeight) {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    // clear all relevant buffers
    glClearColor(0, 0, 0, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
}

void ShadowMapFbo::renderToQuad(int width, int height) {
    debugShader.use();
    FBO::renderToQuad(width, height);
}

