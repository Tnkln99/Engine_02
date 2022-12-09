#include "MeshRenderer.h"
#include "../Object.h"
#include "Mesh.h"
#include "../Assets.h"

MeshRenderer::MeshRenderer() : RenderComponent("mesh renderer")
{
    material = Assets::getMaterial("Default");
    mesh = nullptr;
}

void MeshRenderer::load(Object *owner) {
    Component::load(owner);
    owner->addRenderComponents(this);
    mesh = getOwner()->findComponentByType<Mesh>();
    if (mesh == nullptr){
        mesh = new Mesh;
        mesh->load(owner);
    }
}

void MeshRenderer::setMaterial(const Material & material){
    this->material = material;
}

void MeshRenderer::setMesh(Mesh * mesh){
    this->mesh = mesh;
}

Material & MeshRenderer::getMaterial(){
    return material;
}

Mesh *MeshRenderer::getMesh() {
    return mesh;
}

Component *MeshRenderer::clone() {
    return new MeshRenderer(*this);
}
