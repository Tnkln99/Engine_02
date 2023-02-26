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

void Mesh::load() {
    GLuint EBO, VBO;
    // Generate the VAO and VBO with only 1 object each
    glGenVertexArrays(1, &id);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Make the VAO the current Vertex Array Object by binding it
    glBindVertexArray(id);

    // Bind the VBO_N specifying it's a GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Introduce the positions into the VBO
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);


    // Bind the EBO specifying it's a GL_ELEMENT_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // Introduce the indices into the EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);


    // Setup vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

    glBindVertexArray(0);
}








