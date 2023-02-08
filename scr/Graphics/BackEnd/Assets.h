#ifndef ASSETS_H
#define ASSETS_H

#include <map>
#include <string>


#include "../../Core/Embedded Components/Material.h"
#include "Shader.h"
#include "Texture.h"


class Assets {
public:
    // Resource storage
    static std::map<std::string, Material> materials;

    static std::map<std::string, Shader> shaders;
    static std::map<std::string, Texture2D> textures;


    static Material loadBasicMaterial();

    static Material &getMaterial(const std::string &name);

    static Shader &getShader(const std::string &name);
    static Texture2D &getTexture(const std::string &name);

    static void addTexture(const std::string &nameTexture, const std::string &file);
    static void addShader(const std::string &nameShader,
                          const std::string &vShaderFile = "",
                          const std::string &fShaderFile = "",
                          const std::string &tcShaderFile = "", const std::string &teShaderFile = "",
                          const std::string &gShaderFile = "");

    static void setTexture(const std::string &nameMaterial, const std::string &nameTexture);
    static void setShader(const std::string &nameMaterial, const std::string &nameShader);

    static Texture2D loadTextureFromFile(const std::string &file);
    static Shader loadShaderFromFile(const std::string &vShaderFile = "",
                                       const std::string &fShaderFile = "",
                                       const std::string &tcShaderFile = "", const std::string &teShaderFile = "",
                                       const std::string &gShaderFile = "");


    static void clear();
private:
    Assets() {};
};

#endif