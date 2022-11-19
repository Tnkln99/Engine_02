#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "Engine.h"
#include "Object.h"

Engine::Engine() {
    loadWindow();

    Assets::loadShader("shaders/default.vert", "shaders/default.frag", "shaders/default.tesc", "shaders/default.tese", "", "Default");
    Assets::loadShader("shaders/normals/normal.vert", "shaders/normals/normal.frag", "", "", "shaders/normals/normal.geom", "DefaultN");

    shader = Assets::getShader("Default");

    //t->tore c->cube s->sphere
    mesh.loadPreMade('i');

    object = new Object {0, 0, 0, &mesh};
    object2 = new Object {0, 0, -5, &mesh};

    projMatrix = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -10.0f));

    showNormals = false;
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
    // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
    glViewport(0, 0, (int)windowWidth, (int)windowHeight);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);
}

void Engine::run() {

    while (!glfwWindowShouldClose(window))
    {
        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
    changeViewMode();

    viewMatrix = glm::rotate(viewMatrix, -5.0f * glm::radians(0.05f) * glm::radians(10.0f), glm::vec3(0.5f, 1.0f, 0.0f));

    object->update();
    object2->update();
}

void Engine::changeViewMode() {
    int stateE = glfwGetKey(window, GLFW_KEY_E);
    int stateW = glfwGetKey(window, GLFW_KEY_W);
    int stateQ = glfwGetKey(window, GLFW_KEY_Q);
    int stateN = glfwGetKey(window, GLFW_KEY_N);
    int stateM = glfwGetKey(window, GLFW_KEY_M);

    if (stateE == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }
    else if (stateW == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else if (stateQ == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    if(stateN == GLFW_PRESS)
        showNormals = true;
    else if(stateM ==GLFW_PRESS)
        showNormals = false;
}

void Engine::draw() {
    if(showNormals){
        shader = Assets::getShader("DefaultN");

        shader.use();

        shader.setMatrix4("proj_matrix", projMatrix);
        shader.setMatrix4("view_matrix", viewMatrix);

        object->draw(shader);
        object2->draw(shader);
    }
    shader = Assets::getShader("Default");
    shader.use();

    shader.setMatrix4("proj_matrix", projMatrix);
    shader.setMatrix4("view_matrix", viewMatrix);

    object->draw(shader);
    object2->draw(shader);
}

GLFWwindow* Engine::getWindow() const {
    return window;
}
