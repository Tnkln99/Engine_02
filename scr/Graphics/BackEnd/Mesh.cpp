#include "Mesh.h"



Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
    this->vertices = vertices;
    this->indices = indices;
    material.textures = textures;
}
Mesh::~Mesh() = default;

unsigned int & Mesh::getId() {
    return id;
}

const std::vector<unsigned int> &Mesh::getIndices() {
    return indices;
}

const std::vector<Vertex> &Mesh::getVertices() {
    return vertices;
}

const std::vector<Texture> &Mesh::getTextures() {
    return material.textures;
}

std::vector<glm::vec3> Mesh::computeVertexNormals(const std::vector<glm::vec3>& positions) {
    std::vector<glm::vec3> normals;
    std::vector<int> nbSeen;
    normals.resize(positions.size(),glm::vec3(0));
    nbSeen.resize(positions.size(), 0);

    for(int i = 0; i < indices.size() - 3; i+=3){
        unsigned int ia = indices[i];
        unsigned int ib = indices[i+1];
        unsigned int ic = indices[i+2];

        glm::vec3 aPos = positions[ia];

        glm::vec3 bPos = positions[ib];

        glm::vec3 cPos = positions[ic];

        glm::vec3 e1 = bPos - aPos;
        glm::vec3 e2 = cPos - aPos;
        glm::vec3 no = cross( e1, e2 );

        normals[ia] += no;

        normals[ib] += no;

        normals[ic] += no;
    }

    for(int i = 0; i < positions.size(); i++){
        normals[i] = glm::normalize(normals[i]);
    }

    return normals;
}








