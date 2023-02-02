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

    window = glfwCreateWindow(windowWidth, windowHeight, "Engine_02", glfwGetPrimaryMonitor(), NULL);

    // Error check if the window fails to create
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    // Introduce the window into the current context
    glfwMakeContextCurrent(window);
    // ola

    //Load GLAD so it configures OpenGL
    gladLoadGL();


    renderer.load();
    screenFbo.load(1619,838);
}

void Window::loadUi() {
    ui.load(window, screenFbo);
}


void Window::render(Scene &scene) {
    // rendering the scene to the normal screenFbo
    // todo bind should take parameters to change background color
    screenFbo.bind();
    renderer.forwardRender(scene);
    screenFbo.unbind(windowWidth, windowHeight);

    // imgui will render our texture automatic
    ui.render(scene);

    swapBuffer();
    getEvents();
}


void Window::update() {
    ui.update();
}

// todo: Make an Input class
void Window::getInputs(){
    int stateT = glfwGetKey(window, GLFW_KEY_T);
    int stateY = glfwGetKey(window, GLFW_KEY_Y);
    int stateU = glfwGetKey(window, GLFW_KEY_U);

    if (stateT == GLFW_PRESS)
    {
        renderer.setRenderMode(3);
    }
    else if (stateY == GLFW_PRESS)
    {
        renderer.setRenderMode(2);
    }
    else if (stateU == GLFW_PRESS)
    {
        renderer.setRenderMode(1);
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

glm::vec2 Window::getSceneWindowSize() const {
    glm::vec2 sceneSize{screenFbo.getTextureWidth(), screenFbo.getTextureHeight()};
    return sceneSize;
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

void Window::swapBuffer() {
    glfwSwapBuffers(window);
}

void Window::getEvents() {
    // Take care of all GLFW events
    glfwPollEvents();
}

void Window::clean() {
    ui.terminate();
    renderer.cleanRenderer();
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
}

bool Window::canGetSceneInput() const {
    return ui.getOnSceneUi();
}
