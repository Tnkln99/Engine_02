#include "Scene01_TessGeomShaders.h"
#include "../RenderableObject.h"
#include "../Camera.h"

Scene01_TessGeomShaders::Scene01_TessGeomShaders() { }

Scene01_TessGeomShaders::~Scene01_TessGeomShaders(){
    clean();
}

void Scene01_TessGeomShaders::load(GLFWwindow * window){
    Assets::loadShader("../shaders/Scene01/default.vert", "../shaders/Scene01/default.frag", "../shaders/Scene01/default.tesc", "../shaders/Scene01/default.tese", "../shaders/Scene01/default.geom", "Default");

    shader = Assets::getShader("Default");

    //t->tore c->cube s->sphere
    mesh.loadPreMade('i');

    object = new RenderableObject {0, 0, 0, &mesh};
    camera = new Camera(0, 0, 3, window);
}

void Scene01_TessGeomShaders::clean(){
    object->clean();
}

void Scene01_TessGeomShaders::update(float dt) {
    innerTess = Maths::abs(Maths::sin((float)glfwGetTime() * 0.05f)) * 5;
    outerTess = Maths::abs(Maths::cos((float)glfwGetTime() * 0.5f)) * 3;

    camera->update();
}

void Scene01_TessGeomShaders::draw() {
    shader.use();

    shader.setFloat("innerTess", innerTess);
    shader.setFloat("outerTess", outerTess);

    shader.setMatrix4("proj_matrix", camera->getProjMatrix());
    shader.setMatrix4("view_matrix", camera->getViewMatrix());

    object->draw(shader, GL_PATCHES);
}

void Scene01_TessGeomShaders::addInput(GLFWwindow *window, float deltaTime) { 
    camera->getCameraInput(window, deltaTime);
}




