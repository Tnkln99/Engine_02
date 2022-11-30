#include "RenderableObject.h"
#include "Shader.h"
#include "Mesh.h"

RenderableObject::RenderableObject(float xP, float yP, float zP, Mesh *mesh) : mesh{ mesh } , Object(xP, yP, zP) {

}

void RenderableObject::draw(Shader& shader, GLenum face) {
    shader.setMatrix4("transform", getTransform().getMoveMatrix());
    mesh->draw(face);
}

void RenderableObject::clean(){
    mesh->clean();
}