#include "Scene02_VertexNormals.h"
#include "../Object.h"

Scene02_VertexNormals::Scene02_VertexNormals() {

}

Scene02_VertexNormals::~Scene02_VertexNormals() {
    clean();
}

void Scene02_VertexNormals::load(float windowWidth, float windowHeight) {
    Assets::loadShader("shaders/Scene02/normal.vert", "shaders/Scene02/normal.frag", "", "", "shaders/Scene02/normal.geom", "Default");

    shader = Assets::getShader("Default");

    //t->tore c->cube s->sphere
    mesh.loadPreMade('s');

    object = new Object {0, 0, 0, &mesh};
    //object2 = new Object {0, 0, -5, &mesh};

    projMatrix = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -10.0f));
}

void Scene02_VertexNormals::clean() {
    object->clean();
}

void Scene02_VertexNormals::update() {
    viewMatrix = glm::rotate(viewMatrix, -5.0f * glm::radians(0.05f) * glm::radians(10.0f), glm::vec3(0.5f, 1.0f, 0.0f));

    object->update();
}

void Scene02_VertexNormals::draw() {
    shader.use();
    shader.setMatrix4("proj_matrix", projMatrix);
    shader.setMatrix4("view_matrix", viewMatrix);

    object->draw(shader);
}
