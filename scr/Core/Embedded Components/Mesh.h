#ifndef ENGINE_02_MESH_H
#define ENGINE_02_MESH_H

#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <cmath>

struct Vertex{
    glm::vec3 positions;
    glm::vec3 normals;
};

class Mesh{
private:
    unsigned int id;
    char typeOfMesh;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
public:
    Mesh(char c);
    ~Mesh();

    unsigned int & getId();
    [[nodiscard]] char getTypeOfMesh() const;
    const std::vector<unsigned int> & getIndices();
    const std::vector<Vertex> & getVertices();

    void loadPreMade(char c);

    std::vector<glm::vec3> computeVertexNormals(const std::vector<glm::vec3>& positions);
    void loadCustomMesh(const std::string & objFile, const std::string & materialDir);

    void fillVertices(const std::vector<glm::vec3>& positions, const std::vector<glm::vec3>& normals);
};

#endif
