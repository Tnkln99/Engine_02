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
    std::vector<GLfloat> positions;
    std::vector<GLfloat> normals;
};


class Mesh {
private:
    GLuint VAO;

    Vertex vertices;
    std::vector<GLuint> connections;
public:
    void loadPreMade(char c);

    void draw();
    void clean();

    void computeNormals();

    void generateSphere(int nX, int nY);
    void generateTore(int nX, int nY);
    void generateCube();
    void generateIcosahedron();

    void putDots(float a, float b, float c);
    void connectDots(int a, int b, int c);
};

#endif