#include "Scene04_CameraSandBox.h"
#include "../Object.h"
#include "../Camera.h"


Scene04_CameraSandBox::Scene04_CameraSandBox() { }

Scene04_CameraSandBox::~Scene04_CameraSandBox() {
    clean();
}

void Scene04_CameraSandBox::load(GLFWwindow * window) {
    Assets::loadShader("shaders/Scene04/default.vert", "shaders/Scene04/default.frag", "", "", "shaders/Scene04/default.geom", "Default");

    shader = Assets::getShader("Default");

    //t->tore c->cube s->sphere
    mesh.loadPreMade('i');

    object = new Object {0, 0, -10, &mesh};
    //object2 = new Object {0, 0, -5, &mesh};

    int windowWidth;
    int windowHeight;

    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    projMatrix = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

    camera = new Camera(window);
}

void Scene04_CameraSandBox::clean() {

}

void Scene04_CameraSandBox::update() {
    object->update();
    camera->update();
}

void Scene04_CameraSandBox::draw() {
    shader.use();

    shader.setMatrix4("proj_matrix", projMatrix);
    shader.setMatrix4("view_matrix", camera->getViewMatrix());

    object->draw(shader, GL_TRIANGLES);
}

void Scene04_CameraSandBox::addInput(GLFWwindow *window) {
    camera->getCameraInput(window);
}
