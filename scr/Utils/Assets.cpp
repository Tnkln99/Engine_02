#include "Assets.h"
#include "Log.h"

#include <iostream>
#include <memory>

// Instantiate static variables
std::map<std::string, Material> Assets::materials;
std::map<std::string, ShaderGL> Assets::shaders;
//std::map<std::string, Texture2D> Assets::textures;
//std::map<std::string, TextureKtx> Assets::ktxTextures;
//std::map<std::string, ComputeShader> Assets::computeShaders;

Material Assets::loadMaterial(const std::string &name) {
    shaders["Default"] = loadShaderFromFile("Default" ,"../assets/shaders/default.vert", "../assets/shaders/default.frag", "", "", "");
    materials[name].setShaderId("Default");
    return materials[name];
}

Material & Assets::getMaterial(const std::string &name) {
    return materials[name];
}

ShaderGL &Assets::getShader(const std::string &name) {
    return shaders[name];
}

void Assets::clear() {
    // (Properly) delete all shaders
    for (auto iter : shaders)
        glDeleteProgram(iter.second.id);


    /*for (auto iter : computeShaders)
        glDeleteProgram(iter.second.id);
    // (Properly) delete all textures
    for (auto iter : textures)
        glDeleteTextures(1, &iter.second.id);
    for (auto iter : ktxTextures)
        glDeleteTextures(1, &iter.second.id);*/
}

ShaderGL Assets::loadShaderFromFile(const std::string &name,
                                    const std::string &vShaderFile, const std::string &fShaderFile,
                                    const std::string &tcShaderFile, const std::string &teShaderFile,
                                    const std::string &gShaderFile) {
    // 1. Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string tcCode;
    std::string teCode;
    std::string geometryCode;
    try {
        // Open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // Read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // If tess control shader path is present, also loadCube a tess control shader
        if (tcShaderFile != "") {
            std::ifstream tessControlShaderFile(tcShaderFile);
            std::stringstream tcShaderStream;
            tcShaderStream << tessControlShaderFile.rdbuf();
            tessControlShaderFile.close();
            tcCode = tcShaderStream.str();
        }
        // If tess evaluation shader path is present, also loadCube a tess evaluation shader
        if (teShaderFile != "") {
            std::ifstream tessEvalShaderFile(teShaderFile);
            std::stringstream teShaderStream;
            teShaderStream << tessEvalShaderFile.rdbuf();
            tessEvalShaderFile.close();
            teCode = teShaderStream.str();
        }
        // If geometry shader path is present, also loadCube a geometry shader
        if (gShaderFile != "") {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e) {
        std::ostringstream loadError;
        std::string geomShaderFile = "";
        if (gShaderFile != "")
            geomShaderFile = gShaderFile;

        loadError << "ERROR::SHADER: Failed to read shader files " << vShaderFile << " " << fShaderFile << " "
                  << geomShaderFile << "\n"
                  << "\n -- --------------------------------------------------- -- "
                  << std::endl;
        LOG(Error) << loadError.str();
    }
    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();
    const GLchar *tcShaderCode = tcCode.c_str();
    const GLchar *teShaderCode = teCode.c_str();
    const GLchar *gShaderCode = geometryCode.c_str();
    // 2. Now create shader object from source code
    ShaderGL shader;
    shader.compile(vShaderCode, fShaderCode,
                   tcShaderFile != "" ? tcShaderCode : nullptr,
                   teShaderFile != "" ? teShaderCode : nullptr,
                   gShaderFile != "" ? gShaderCode : nullptr);
    std::cout<<"shaders sucessfully loaded "<<std::endl;
    return shader;
}



/*

Texture2D Assets::loadTexture(const std::string &file, const std::string &name) {
    textures[name] = loadTextureFromFile(file.c_str());
    return textures[name];
}

Texture2D& Assets::getTexture(const std::string &name) {
    return textures[name];
}

ComputeShader Assets::loadComputeShader(const std::string &cShaderFile, const std::string &name) {
    computeShaders[name] = loadComputeShaderFromFile(cShaderFile);
    return computeShaders[name];
}

ComputeShader& Assets::getComputeShader(const std::string &name) {
    return computeShaders[name];
}

TextureKtx Assets::loadTextureKtx(const std::string &file, const std::string &name) {
    auto texture = TextureKtx();
    texture.loadCube(file.c_str(), texture.id);
    ktxTextures[name] = texture;
    return ktxTextures[name];
}

TextureKtx& Assets::getTextureKtx(const std::string &name) {
    return ktxTextures[name];
}



ComputeShader Assets::loadComputeShaderFromFile(const std::string &cShaderFile) {
    FILE * fp;
    size_t filesize;
    char * source;
    try {
        fp = fopen(cShaderFile.c_str(), "rb");

        fseek(fp, 0, SEEK_END);
        filesize = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        source = new char [filesize + 1];

        fread(source, 1, filesize, fp);
        source[filesize] = 0;
        fclose(fp);
    }
    catch (std::exception e) {
        std::ostringstream loadError;

        loadError << "ERROR::SHADER: Failed to read compute shader files " << cShaderFile << "\n"
                  << "\n -- --------------------------------------------------- -- "
                  << std::endl;
        LOG(Error) << loadError.str();
    }

    ComputeShader shader;
    shader.compile(source);
    delete [] source;
    return shader;
}

Texture2D Assets::loadTextureFromFile(const std::string &file) {
    // Create Texture object
    Texture2D texture;
    texture.loadCube(file);

    // Now generate texture
    texture.generate();
    // And finally return texture
    return texture;
}

 */