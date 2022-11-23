#include "Window.h"

void Window::getInputs() {
    int stateT = glfwGetKey(window, GLFW_KEY_T);
    int stateY = glfwGetKey(window, GLFW_KEY_Y);
    int stateU = glfwGetKey(window, GLFW_KEY_U);

    if (stateT == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }
    else if (stateY == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else if (stateU == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

float Window::getHeight() const{
    return windowHeight;
}

float Window::getWidth() const{
    return windowWidth;
}

void Window::setHeight(float height) {
    windowHeight = height;
}

void Window::setWidth(float width) {
    windowWidth = width;
}

GLFWwindow *Window::getPointer() const {
    return window;
}

void Window::setBackgroundColor(float r, float b, float g, float t) {
    // Specify the color of the background
    glClearColor(r, b, g, t);
}

void Window::swapBuffer() {
    glfwSwapBuffers(window);
}

void Window::clearBuffer() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::load() {
    // Init logging
    LOG_CONFIG.reporting_level = Debug;
    LOG_CONFIG.restart = true;
    if (LOG_CONFIG.restart) {
        Log::restart();
    }
    // Initialize GLFW
    glfwInit();

    // Tell GLFW what version of OpenGL we are using
    // In this case we are using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we are using the CORE profile
    // So that means we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFWwindow object of 800 by 800 pixels, naming it "Engine"
    window = glfwCreateWindow((int)windowWidth, (int)windowHeight, "Engine_02", NULL, NULL);
    // Error check if the window fails to create
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    // Introduce the window into the current context
    glfwMakeContextCurrent(window);

    //Load GLAD so it configures OpenGL
    gladLoadGL();
    // Specify the viewport of OpenGL in the Window
    glViewport(0, 0, (int)windowWidth, (int)windowHeight);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);
}

void Window::getEvents() {
    // Take care of all GLFW events
    glfwPollEvents();
}

void Window::clean() {
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
}


