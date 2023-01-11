#ifndef ENGINE_02_MESH_H
#define ENGINE_02_MESH_H

#include "glad/glad.h"
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
    explicit Mesh(char c);
    ~Mesh();

    unsigned int & getId();
    [[nodiscard]] char getTypeOfMesh() const;
    const std::vector<unsigned int> & getIndices();
    const std::vector<Vertex> & getVertices();

    void loadPreMade(char c);

    std::vector<glm::vec3> computeVertexNormals(const std::vector<glm::vec3>& positions);
    void fillVertices(const std::vector<glm::vec3>& positions, const std::vector<glm::vec3>& normals);

    void generateSphere(int nX, int nY);
    void generateTore(int nX, int nY);
    void generateCube();
    void generateIcosahedron();

    void connectDots(int a, int b, int c);
};

#endif
