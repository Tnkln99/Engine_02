#include "ModelC.h"
#include "../Scene.h"


ModelC::ModelC() : Component("model"){

}

ModelC::~ModelC() {

}

void ModelC::load(Object *owner) {
    Component::load(owner);
    model = owner->getScene()->getModelManager().addModel("../assets/models/cube/cube.obj");
}

void ModelC::reloadModel(Object *owner, char * modelPath) {
    model = owner->getScene()->getModelManager().addModel(modelPath, model);
}

std::shared_ptr<Model> ModelC::getModel() {
    return model;
}

Component * ModelC::clone() {
    return new ModelC(*this);
}