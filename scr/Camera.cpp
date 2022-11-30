#include "Camera.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>



Camera::Camera(float x, float y, float z, GLFWwindow * window) : Object(x, y, z){ 
    view = glm::lookAt(transform.getPosition(), transform.getPosition() + transform.getDirection(), cameraUp);

    int windowWidth;
    int windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    projMatrix = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

    glfwSetWindowUserPointer( window, this );

    glfwSetCursorPosCallback( window, []( GLFWwindow* window, double x, double y )
    {
        Camera* camera = static_cast<Camera*>( glfwGetWindowUserPointer( window ) );
        camera->mouse_callback( x, y );
    } );
}

void Camera::getCameraInput(GLFWwindow * window, float dt) {    
    float cameraSpeed = 6.0f * dt;

    glm::vec3 cameraPos = transform.getPosition();
    glm::vec3 cameraFront = transform.getDirection();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    transform.setPosition(cameraPos);

    int mouseState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

    if(mouseState == GLFW_PRESS){
        mouseClicked = true;
    }
    else{
        mouseClicked = false;
        double xpos, ypos;
        //getting cursor position
        glfwGetCursorPos(window, &xpos, &ypos);
        lastMouseX = xpos;
        lastMouseY = ypos;
    }
}

void Camera::mouse_callback(double xpos, double ypos) {
    if (firstMouse)
    {
        lastMouseX = xpos;
        lastMouseY = ypos;
        firstMouse = false;
    }

    if (!mouseClicked)
        return;

    float xoffset = xpos - lastMouseX;
    float yoffset = lastMouseY - ypos;

    float sensitivity = 0.005f;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    transform.computeDirection(yaw, pitch);
}

void Camera::update() {
    view = glm::lookAt(transform.getPosition(), transform.getPosition() + transform.getDirection(), cameraUp);
}

const glm::mat4 & Camera::getViewMatrix() {
    return view;
}

const glm::mat4 & Camera::getProjMatrix() {
    return projMatrix;
}


