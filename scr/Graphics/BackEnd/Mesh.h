#ifndef ENGINE_02_MESH_H
#define ENGINE_02_MESH_H

#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <cmath>

struct Vertex{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

struct Texture{
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh{
private:
    unsigned int id{};
    std::string nameOfMesh{};

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    ~Mesh();

    unsigned int & getId();
    const std::vector<unsigned int> & getIndices();
    const std::vector<Vertex> & getVertices();
    const std::vector<Texture> & getTextures();

    std::vector<glm::vec3> computeVertexNormals(const std::vector<glm::vec3>& positions);
};

#endif
