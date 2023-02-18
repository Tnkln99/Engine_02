#include "ModelRendererC.h"
#include "../Object.h"
#include "ModelC.h"
#include "../../Graphics/BackEnd/Assets.h"

ModelRendererC::ModelRendererC() : Component("model renderer")
{
    material = Assets::getMaterial("Default");
    mesh = nullptr;
}

ModelRendererC::~ModelRendererC() {

}

void ModelRendererC::load(Object *owner) {
    Component::load(owner);
    owner->addRenderComponents(this);
    mesh = getOwner()->findComponentByType<ModelC>();
    if (mesh == nullptr){
        mesh = new ModelC;
        mesh->load(owner);
    }
}

void ModelRendererC::setMaterial(const Material & material){
    this->material = material;
}

void ModelRendererC::setModelC(ModelC * mesh){
    this->mesh = mesh;
}

Material & ModelRendererC::getMaterial(){
    return material;
}

ModelC *ModelRendererC::getModelC() {
    return mesh;
}


int ModelRendererC::getRenderOrder() const {
    return renderOrder;
}

Component *ModelRendererC::clone() {
    return new ModelRendererC(*this);
}





