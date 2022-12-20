#include "Window.h"

void Window::load() {

    // Initialize GLFW
    glfwInit();

    // Tell GLFW what version of OpenGL we are using
    // In this case we are using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we are using the CORE profile
    // So that means we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    windowWidth = mode->width;
    windowHeight = mode->height;

    window = glfwCreateWindow(windowWidth, windowHeight, "Engine_02", NULL, NULL);

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
    glViewport(0, 0, windowWidth, windowHeight);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);

    framebuffer.load();
}


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
    return (float)windowHeight;
}

float Window::getWidth() const{
    return (float)windowWidth;
}

void Window::setHeight(int height) {
    windowHeight = height;
}

void Window::setWidth(int width) {
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

void Window::drawToFrameBuffer() {
    //glActiveTexture(GL_TEXTURE0);
    framebuffer.renderToTexture();
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

void Window::bindToFrameBuffer() {
    framebuffer.bind();
}

int Window::getRenderTexture() {
    return framebuffer.getTexture();
}

