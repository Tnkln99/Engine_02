#include "Scene02_TestNormals.h"
#include "../Object.h"
#include "../Camera.h"

Scene02_TestNormals::Scene02_TestNormals() { }

Scene02_TestNormals::~Scene02_TestNormals() {
    clean();
}

void Scene02_TestNormals::load(GLFWwindow * window) {
    Assets::loadShader("../shaders/Scene02/normal.vert", "../shaders/Scene02/normal.frag", "", "", "../shaders/Scene02/normal.geom", "Normals");
    Assets::loadShader("../shaders/Scene02/default.vert", "../shaders/Scene02/default.frag", "", "", "", "Default");

    shader = Assets::getShader("Default");

    //t->tore c->cube s->sphere
    mesh.loadPreMade('i');

    object = new Object {0, 0, 0, &mesh};
    camera = new Camera(window);
    //object2 = new Object {0, 0, -5, &mesh};

    int windowWidth;
    int windowHeight;

    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    showNormals = false;
}

void Scene02_TestNormals::clean() {
    object->clean();
}

void Scene02_TestNormals::update() {
    object->update();
    camera->update();
}

void Scene02_TestNormals::draw() {
    shader = Assets::getShader("Default");

    shader.use();
    shader.setMatrix4("proj_matrix", camera->getProjMatrix());
    shader.setMatrix4("view_matrix", camera->getViewMatrix());

    object->draw(shader, GL_TRIANGLES);
    if (showNormals){
        shader = Assets::getShader("Normals");

        shader.use();
        shader.setMatrix4("proj_matrix", camera->getProjMatrix());
        shader.setMatrix4("view_matrix", camera->getViewMatrix());

        object->draw(shader, GL_TRIANGLES);
    }
}

void Scene02_TestNormals::addInput(GLFWwindow *window) {
    camera->getCameraInput(window);

    int stateN = glfwGetKey(window, GLFW_KEY_N);
    int stateM = glfwGetKey(window, GLFW_KEY_M);

    if (stateN == GLFW_PRESS)
    {
        showNormals = true;
    }
    if (stateM == GLFW_PRESS)
    {
        showNormals = false;
    }
}


