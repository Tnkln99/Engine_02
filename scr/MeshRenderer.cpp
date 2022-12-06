#include "MeshRenderer.h"
#include "Object.h"
#include "Mesh.h"
#include "Assets.h"
#include "EngineRenderer.h"

MeshRenderer::MeshRenderer(Object * owner) : RenderComponent(owner, "mesh renderer")
{
    material = Assets::getMaterial("Default");
    mesh = getOwner()->findComponentByType<Mesh>();
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

void MeshRenderer::onComponentAdd(){
    mesh = getOwner()->findComponentByType<Mesh>();
}

Mesh *MeshRenderer::getMesh() {
    return mesh;
}
