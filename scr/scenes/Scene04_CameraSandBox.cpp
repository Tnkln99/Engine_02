#include "Scene04_CameraSandBox.h"
#include "../Object.h"
#include "../Camera.h"


Scene04_CameraSandBox::Scene04_CameraSandBox() { }

Scene04_CameraSandBox::~Scene04_CameraSandBox() {
    clean();
}

void Scene04_CameraSandBox::load(GLFWwindow * window) {
    Assets::loadShader("../shaders/Scene04/default.vert", "../shaders/Scene04/default.frag", "", "", "../shaders/Scene04/default.geom", "Default");

    shader = Assets::getShader("Default");

    //t->tore c->cube s->sphere
    mesh.loadPreMade('i');

    object = new Object {0, 0, -10, &mesh};
    object2 = new Object {0, 0, -5, &mesh};

    camera = new Camera(window);
}

void Scene04_CameraSandBox::clean() {

}

void Scene04_CameraSandBox::update() {
    object->update();
    object2->update();

    camera->update();
}

void Scene04_CameraSandBox::draw() {
    shader.use();

    shader.setMatrix4("proj_matrix", camera->getProjMatrix());
    shader.setMatrix4("view_matrix", camera->getViewMatrix());

    object->draw(shader, GL_TRIANGLES);
    object2->draw(shader, GL_TRIANGLES);
}

void Scene04_CameraSandBox::addInput(GLFWwindow *window) {
    camera->getCameraInput(window);
}
