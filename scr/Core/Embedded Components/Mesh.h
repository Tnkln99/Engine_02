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
    unsigned int id{};
    std::string nameOfMesh{};

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
public:
    Mesh(const std::string & objFile, const std::string & materialDir);
    Mesh(const std::string & c);
    ~Mesh();

    unsigned int & getId();
    [[nodiscard]] const std::string & getNameOfMesh() const;
    const std::vector<unsigned int> & getIndices();
    const std::vector<Vertex> & getVertices();

    void loadPreMade(const std::string & c);

    std::vector<glm::vec3> computeNormals(const std::vector<glm::vec3>& positions);
    void load(const std::string & objFile, const std::string & materialDir);

    void fillVertices(const std::vector<glm::vec3>& positions, const std::vector<glm::vec3>& normals);
};

#endif
