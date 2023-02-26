#include "EngineCamera.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>



EngineCamera::EngineCamera(GLFWwindow * window, float sceneWidth, float sceneHeight, float x, float y, float z) {
    transform.setPosition(glm::vec3(x,y,z));
    view = glm::lookAt(transform.getPosition(), transform.getPosition() + transform.getDirection(), cameraUp);

    // todo: this should be with texture width and texture height
    projMatrix = glm::perspective(glm::radians(45.0f), (float)sceneWidth / (float)sceneHeight, 0.1f, 100.0f);

    glfwSetWindowUserPointer( window, this );

    glfwSetCursorPosCallback( window, []( GLFWwindow* window, double x, double y )
    {
        EngineCamera* camera = static_cast<EngineCamera*>( glfwGetWindowUserPointer( window ) );
        camera->mouse_callback( x, y );
    } );
}

void EngineCamera::getCameraInput(GLFWwindow * window, float dt) {    
    float cameraSpeed = 6.0f * dt;

    glm::vec3 cameraPos = transform.getPosition();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * transform.getDirection();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * transform.getDirection();
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(transform.getDirection(), cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(transform.getDirection(), cameraUp)) * cameraSpeed;

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

void EngineCamera::mouse_callback(double xpos, double ypos) {
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

void EngineCamera::update() {
    view = glm::lookAt(transform.getPosition(), transform.getPosition() + transform.getDirection(), cameraUp);
}

const glm::mat4 & EngineCamera::getViewMatrix() {
    return view;
}

const glm::mat4 & EngineCamera::getProjMatrix() {
    return projMatrix;
}

const Transform &EngineCamera::getTransform() {
    return transform;
}


