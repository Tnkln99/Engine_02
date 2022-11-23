#include "Camera.h"
#include <glm/ext/matrix_transform.hpp>



Camera::Camera(GLFWwindow * window) {
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    int windowWidth;
    int windowHeight;

    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    lastMouseX = (float)windowWidth / 2;
    lastMouseY = (float)windowHeight / 2;

    glfwSetWindowUserPointer( window, this );

    glfwSetCursorPosCallback( window, []( GLFWwindow* window, double x, double y )
    {
        Camera* camera = static_cast<Camera*>( glfwGetWindowUserPointer( window ) );
        camera->mouse_callback( x, y );
    } );
}

void Camera::getCameraInput(GLFWwindow * window) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    float cameraSpeed = 6.0f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

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

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void Camera::update() {
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

glm::mat4 Camera::getViewMatrix() {
    return view;
}


