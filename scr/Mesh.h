#ifndef CUBEMESH_H
#define CUBEMESH_H

#define _USE_MATH_DEFINES

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#include "Component.h"

struct Vertex{
    glm::vec3 positions;
    glm::vec3 normals;
};

class Object;

class Mesh : public Component{
private:
    unsigned int id;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
public:
    explicit Mesh(Object * owner);

    unsigned int & getId();
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