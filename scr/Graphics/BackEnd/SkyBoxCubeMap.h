#ifndef ENGINE_02_SKYBOXCUBEMAP_H
#define ENGINE_02_SKYBOXCUBEMAP_H

#include <vector>
#include <string>
#include <iostream>
#include "Shader.h"


class SkyBoxCubeMap {
private:
    Shader skyBoxShader;

    unsigned int textureID{};
    unsigned int skyboxVAO{};
    std::vector<std::string> faces
    {
        "../assets/skyBox/right.jpg",
        "../assets/skyBox/left.jpg",
        "../assets/skyBox/top.jpg",
        "../assets/skyBox/bottom.jpg",
        "../assets/skyBox/front.jpg",
        "../assets/skyBox/back.jpg"
    };
public:
    void load();

    void renderToSkyBox(glm::mat4 view, glm::mat4 projection);
};


#endif //ENGINE_02_SKYBOXCUBEMAP_H
