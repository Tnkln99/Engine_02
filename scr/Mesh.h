#ifndef CUBEMESH_H
#define CUBEMESH_H

#define _USE_MATH_DEFINES

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <cmath>

struct Vertex{
    glm::vec3 positions;
    glm::vec3 normals;
};


class Mesh {
private:
    GLuint VAO;

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    bool showNormals = false;
public:
    void loadPreMade(char c);

    void draw(GLenum face);
    void clean();

    std::vector<glm::vec3> computeNormals(const std::vector<glm::vec3>& positions);
    void fillVertices(const std::vector<glm::vec3>& positions, const std::vector<glm::vec3>& normals);

    void generateSphere(int nX, int nY);
    void generateTore(int nX, int nY);
    void generateCube();
    void generateIcosahedron();

    void connectDots(int a, int b, int c);
};

#endif