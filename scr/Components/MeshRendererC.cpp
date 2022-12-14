#include "MeshRendererC.h"
#include "../Object.h"
#include "MeshC.h"
#include "../Assets.h"

MeshRendererC::MeshRendererC() : RenderComponent("mesh renderer")
{
    material = Assets::getMaterial("Default");
    mesh = nullptr;
}

MeshRendererC::~MeshRendererC() {
    delete mesh;
}

void MeshRendererC::load(Object *owner) {
    Component::load(owner);
    owner->addRenderComponents(this);
    mesh = getOwner()->findComponentByType<MeshC>();
    if (mesh == nullptr){
        mesh = new MeshC;
        mesh->load(owner);
    }
}

void MeshRendererC::setMaterial(const Material & material){
    this->material = material;
}

void MeshRendererC::setMeshC(MeshC * mesh){
    this->mesh = mesh;
}

Material & MeshRendererC::getMaterial(){
    return material;
}

MeshC *MeshRendererC::getMeshC() {
    return mesh;
}

Component *MeshRendererC::clone() {
    return new MeshRendererC(*this);
}




