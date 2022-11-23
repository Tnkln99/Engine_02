#ifndef ENGINE_02_CAMERA_H
#define ENGINE_02_CAMERA_H

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

class Camera {
private:
    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frameu

    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

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
    Camera(GLFWwindow * window);

    const glm::mat4 & getViewMatrix();
    const glm::mat4 & getProjMatrix();

    void getCameraInput(GLFWwindow * window);
    void mouse_callback(double xpos, double ypos);

    void update();
};


#endif //ENGINE_02_CAMERA_H
