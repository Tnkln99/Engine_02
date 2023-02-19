#ifndef ASSETS_H
#define ASSETS_H

#include <map>
#include <string>


#include "Material.h"
#include "Shader.h"
#include "Texture.h"


class Assets {
public:
    // Resource storage
    static std::map<std::string, Material> materials;

    static std::map<std::string, Shader> shaders;


    static void loadBasicShader();

    static Shader &getShader(const std::string &name);

    static void addShader(const std::string &nameShader,
                          const std::string &vShaderFile = "",
                          const std::string &fShaderFile = "",
                          const std::string &tcShaderFile = "", const std::string &teShaderFile = "",
                          const std::string &gShaderFile = "");

    static Shader loadShaderFromFile(const std::string &vShaderFile = "",
                                       const std::string &fShaderFile = "",
                                       const std::string &tcShaderFile = "", const std::string &teShaderFile = "",
                                       const std::string &gShaderFile = "");


    static void clear();
private:
    Assets() {};
};

#endif