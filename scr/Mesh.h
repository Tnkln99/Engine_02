#ifndef CUBEMESH_H
#define CUBEMESH_H

#define _USE_MATH_DEFINES

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <cmath>

enum meshType{
    sphere,
    cube
};


class Mesh {
private:
    GLuint VAO;

    std::vector<GLfloat> positionDots;
    std::vector<GLuint> connections;
public:
    void loadPreMade(char c);

    void draw();
    void clean();

    void putDots(float a, float b, float c);
    void connectDots(int a, int b, int c);

    void generateSphere(int nX, int nY);
    void generateCube();
    void generateTore(int nX, int nY);
};

#endif