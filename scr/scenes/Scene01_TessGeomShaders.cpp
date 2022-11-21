#include "Scene01_TessGeomShaders.h"
#include "../Object.h"

Scene01_TessGeomShaders::Scene01_TessGeomShaders() { }

Scene01_TessGeomShaders::~Scene01_TessGeomShaders(){
    clean();
}

void Scene01_TessGeomShaders::load(float windowWidth, float windowHeight){
    Assets::loadShader("shaders/Scene01/default.vert", "shaders/Scene01/default.frag", "shaders/Scene01/default.tesc", "shaders/Scene01/default.tese", "shaders/Scene01/default.geom", "Default");

    shader = Assets::getShader("Default");

    //t->tore c->cube s->sphere
    mesh.loadPreMade('i');

    object = new Object {0, 0, 0, &mesh};
    //object2 = new Object {0, 0, -5, &mesh};

    projMatrix = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -10.0f));
}

void Scene01_TessGeomShaders::clean(){
    object->clean();
}

void Scene01_TessGeomShaders::update() {
    innerTess = Maths::abs(Maths::sin((float)glfwGetTime() * 0.05f)) * 5;
    outerTess = Maths::abs(Maths::cos((float)glfwGetTime() * 0.5f)) * 3;

    viewMatrix = glm::rotate(viewMatrix, -5.0f * glm::radians(0.05f) * glm::radians(10.0f), glm::vec3(0.5f, 1.0f, 0.0f));

    object->update();
    //object2->update();
}

void Scene01_TessGeomShaders::draw() {
    shader.use();

    shader.setFloat("innerTess", innerTess);
    shader.setFloat("outerTess", outerTess);

    shader.setMatrix4("proj_matrix", projMatrix);
    shader.setMatrix4("view_matrix", viewMatrix);

    object->draw(shader, GL_PATCHES);
    //object2->draw(shader);
}

void Scene01_TessGeomShaders::addInput(GLFWwindow *window) { }




