#ifndef ENGINE_02_MESH_H
#define ENGINE_02_MESH_H

#include "Material.h"
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "Assets.h"

struct Vertex{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};


class Mesh{
private:
    unsigned int id{};
    std::string nameOfMesh{};

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
public:
    Material material{&Assets::getShader("Default")};

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    ~Mesh();

    unsigned int & getId();
    const std::vector<unsigned int> & getIndices();
    const std::vector<Vertex> & getVertices();
    const std::vector<Texture> & getTextures();

    std::vector<glm::vec3> computeVertexNormals(const std::vector<glm::vec3>& positions);

    void load();
};

#endif
