#include "Scene03_ToSphere.h"
#include "../Object.h"

Scene03_ToSphere::Scene03_ToSphere() { }

Scene03_ToSphere::~Scene03_ToSphere() {
    clean();
}

void Scene03_ToSphere::load(GLFWwindow * window) {
    Assets::loadShader("shaders/Scene03/default.vert", "shaders/Scene03/default.frag", "shaders/Scene03/default.tesc", "shaders/Scene03/default.tese", "shaders/Scene03/default.geom", "Default");

    shader = Assets::getShader("Default");

    //t->tore c->cube s->sphere
    mesh.loadPreMade('c');

    object = new Object {0, 0, 0, &mesh};
    //object2 = new Object {0, 0, -5, &mesh};

    int windowWidth;
    int windowHeight;

    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    projMatrix = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -10.0f));
}

void Scene03_ToSphere::clean() {
    object->clean();
}

void Scene03_ToSphere::update() {
    viewMatrix = glm::rotate(viewMatrix, -5.0f * glm::radians(0.05f) * glm::radians(10.0f), glm::vec3(0.5f, 1.0f, 0.0f));

    object->update();
}

void Scene03_ToSphere::draw() {
    shader.use();

    shader.setFloat("interp_frac", abs(sin((float)glfwGetTime())));

    shader.setMatrix4("proj_matrix", projMatrix);
    shader.setMatrix4("view_matrix", viewMatrix);

    object->draw(shader, GL_PATCHES);
}

void Scene03_ToSphere::addInput(GLFWwindow *window) {

}
