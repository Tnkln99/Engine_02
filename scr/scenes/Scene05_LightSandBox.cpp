#include "Scene05_LightSandBox.h"
#include "../RenderableObject.h"
#include "../Camera.h"
#include "../Light.h"

Scene05_LightSandBox::Scene05_LightSandBox() { }

Scene05_LightSandBox::~Scene05_LightSandBox() {
    clean();
}

void Scene05_LightSandBox::load(GLFWwindow *window) {
    Assets::loadShader("shaders/Scene05/default.vert", "shaders/Scene05/default.frag", "", "", "", "Default");
    Assets::loadShader("shaders/Scene05/light.vert", "shaders/Scene05/light.frag", "", "", "", "Light");

    shader = Assets::getShader("Default");

    //t->tore c->cube s->sphere
    mesh.loadPreMade('c');

    object = new RenderableObject {0, 0, -10, &mesh};
    light = new Light {5, 0, -10, &mesh};

    light->show(true);

    object->setColor(0.1,0.2,0.2);

    camera = new Camera(window);
}

void Scene05_LightSandBox::clean() {
    object->clean();
}

void Scene05_LightSandBox::update() {
    object->update();
    light->update();
    camera->update();
}

void Scene05_LightSandBox::draw() {
    shader = Assets::getShader("Default");
    shader.use();

    shader.setMatrix4("proj_matrix", camera->getProjMatrix());
    shader.setMatrix4("view_matrix", camera->getViewMatrix());

    //shader.setVector3f("light_color", light->getColor());
    //shader.setVector3f("object_color", object->getColor());

    shader.setVector3f("viewPos", camera->getCameraPos());

    shader.setVector3f("light.position", light->getPosition());
    /* std::cout<<"x: "<< light->getPosition().x << " y: "<<light->getPosition().y << " z: "<< light->getPosition().z <<std::endl;
    std::cout<<"x: "<< object->getPosition().x << " y: "<<object->getPosition().y << " z: "<< object->getPosition().z <<std::endl;
    std::cout<<std::endl; */
    shader.setVector3f("light.ambient",  light->getAmbient());
    shader.setVector3f("light.diffuse",  light->getDiffuse());
    shader.setVector3f("light.specular", light->getSpecular());
    
    shader.setVector3f("material.ambient", object->getAmbient());
    shader.setVector3f("material.diffuse", object->getDiffuse());
    shader.setVector3f("material.specular", object->getSpecular());
    shader.setFloat("material.shininess", object->getShininess());

    object->draw(shader, GL_TRIANGLES);

    if(light->doesShow()){
        shader = Assets::getShader("Light");
        shader.use();

        shader.setMatrix4("proj_matrix", camera->getProjMatrix());
        shader.setMatrix4("view_matrix", camera->getViewMatrix());

        shader.setVector3f("light_color", light->getColor());

        light->draw(shader, GL_TRIANGLES);
    }
}

void Scene05_LightSandBox::addInput(GLFWwindow *window) {
    camera->getCameraInput(window);
}
