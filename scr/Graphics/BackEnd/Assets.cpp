#include "Assets.h"
#include "../../Utils/Log.h"

#include <iostream>
#include <memory>

// Instantiate static variables
std::map<std::string, Material> Assets::materials;

std::map<std::string, Shader> Assets::shaders;

Material Assets::loadBasicMaterial() {
    shaders["Default"] = loadShaderFromFile("../assets/shaders/default.vert", "../assets/shaders/default.frag", "", "", "");
    materials["Default"].setShaderId("Default");
    return materials["Default"];
}

Material & Assets::getMaterial(const std::string &name) {
    return materials[name];
}

Shader &Assets::getShader(const std::string &name) {
    return shaders[name];
}

void Assets::addShader(const std::string &nameShader,
                       const std::string &vShaderFile, const std::string &fShaderFile,
                       const std::string &tcShaderFile, const std::string &teShaderFile,
                       const std::string &gShaderFile) {
    shaders[nameShader] = loadShaderFromFile(vShaderFile, fShaderFile, tcShaderFile, teShaderFile, gShaderFile);
}


void Assets::setShader(const std::string &nameMaterial, const std::string &nameShader) {
    materials[nameMaterial].setShaderId(nameShader);
}

Shader Assets::loadShaderFromFile(const std::string &vShaderFile, const std::string &fShaderFile,
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
    Shader shader;
    shader.compile(vShaderCode, fShaderCode,
                   tcShaderFile != "" ? tcShaderCode : nullptr,
                   teShaderFile != "" ? teShaderCode : nullptr,
                   gShaderFile != "" ? gShaderCode : nullptr);
    std::cout << "shaders sucessfully loaded " << std::endl;
    return shader;
}


void Assets::clear() {
    // (Properly) delete all shaders
    for (auto iter : shaders)
        glDeleteProgram(iter.second.id);
}








