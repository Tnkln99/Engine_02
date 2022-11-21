#include "Scene02_VertexNormals.h"
#include "../Object.h"

Scene02_VertexNormals::Scene02_VertexNormals() { }

Scene02_VertexNormals::~Scene02_VertexNormals() {
    clean();
}

void Scene02_VertexNormals::load(float windowWidth, float windowHeight) {
    Assets::loadShader("shaders/Scene02/normal.vert", "shaders/Scene02/normal.frag", "", "", "shaders/Scene02/normal.geom", "Normals");
    Assets::loadShader("shaders/Scene02/default.vert", "shaders/Scene02/default.frag", "", "", "", "Default");

    shader = Assets::getShader("Default");

    //t->tore c->cube s->sphere
    mesh.loadPreMade('s');

    object = new Object {0, 0, 0, &mesh};
    //object2 = new Object {0, 0, -5, &mesh};

    projMatrix = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -10.0f));

    showNormals = false;
}

void Scene02_VertexNormals::clean() {
    object->clean();
}

void Scene02_VertexNormals::update() {
    //viewMatrix = glm::rotate(viewMatrix, -5.0f * glm::radians(0.05f) * glm::radians(10.0f), glm::vec3(0.5f, 1.0f, 0.0f));

    object->update();
}

void Scene02_VertexNormals::draw() {
    if (showNormals){
        shader = Assets::getShader("Normals");

        shader.use();
        shader.setMatrix4("proj_matrix", projMatrix);
        shader.setMatrix4("view_matrix", viewMatrix);

        object->draw(shader, GL_TRIANGLES);
    }
    shader = Assets::getShader("Default");

    shader.use();
    shader.setMatrix4("proj_matrix", projMatrix);
    shader.setMatrix4("view_matrix", viewMatrix);

    object->draw(shader, GL_TRIANGLES);
}

void Scene02_VertexNormals::addInput(GLFWwindow *window) {
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


