#include "Window.h"
#include "BackEnd/Assets.h"

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

    screenFbo.load(1619,838);
    renderer.load();

    Assets::loadBasicShader();
}

void Window::loadUi() {
    ui.load(window, screenFbo);
}


void Window::render(Scene &scene) {
    // shadow map fbo are in lights
    renderer.renderToShadowMap(scene);

    // rendering the scene to the screenFbo
    screenFbo.bind(0.07f, 0.13f, 0.17f);
    renderer.renderScene(scene, shadowMapFbo.getTexture());
    screenFbo.unbind(windowWidth, windowHeight);

    // imgui will render our texture automatic
    ui.render(scene);

    glfwSwapBuffers(window);
    glfwPollEvents();
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
