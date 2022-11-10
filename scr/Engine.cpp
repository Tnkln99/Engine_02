#include "Engine.h"
#include "Object.h"

Engine::Engine() {
    loadWindow();

    Assets::loadShader("shaders/default.vert", "shaders/default.frag", "", "", "", "Default");
    shader = Assets::getShader("Default");

    //t->tore c->cube s->sphere
    mesh.loadPreMade('i');

    object = new Object {0, 0, &mesh};

    projMatrix =  Matrix4::createPerspectiveFOV(70.0f, 800, 800, 0.1f, 1000.0f);
}

void Engine::loadWindow() {
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

    // Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
    window = glfwCreateWindow(windowWidth, windowHeight, "YoutubeOpenGL", NULL, NULL);
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
    // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
    glViewport(0, 0, windowWidth, windowHeight);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
}

void Engine::run() {
    while (!glfwWindowShouldClose(window))
    {
        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT);

        update();
        draw();

        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }
    terminate();
}

void Engine::terminate() {
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
}

void Engine::update() {
    //TODO: change this timing thing..
    using namespace std::chrono;
    auto tp = system_clock::now() + 0ns;
    double t1 = tp.time_since_epoch().count();
    double t2 = std::nextafter(t1, INFINITY);
    double timeSinceStart = t2-t1;
    object->update(timeSinceStart);
}

void Engine::draw() {
    shader.use();

    shader.setMatrix4("proj_matrix", projMatrix);

    object->draw(shader);
}

GLFWwindow* Engine::getWindow() const {
    return window;
}








