#ifndef ENGINE_02_CAMERA_H
#define ENGINE_02_CAMERA_H
#include "Transformable.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>


class EngineCamera{
private:
    Transformable transform;

    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f,  0.0f);

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projMatrix = glm::mat4(1.0f);

    bool firstMouse = true;
    bool mouseClicked = false;

    float lastMouseX;
    float lastMouseY;

    float yaw   = -90.0f;
    float pitch =  0.0f;
    float fov   =  45.0f;
public:
    EngineCamera(GLFWwindow * window, float x = 0.0f, float y = 0.0f, float z = 0.0f);

    const glm::mat4 & getViewMatrix();
    const glm::mat4 & getProjMatrix();

    void getCameraInput(GLFWwindow * window, float dt);
    void mouse_callback(double xpos, double ypos);

    const Transformable & getTransform();

    void update();
};


#endif //ENGINE_02_CAMERA_H
