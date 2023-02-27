#include "ModelC.h"
#include "../Scene.h"


ModelC::ModelC() : Component("model"){

}

ModelC::~ModelC() {

}

void ModelC::load(Object *owner) {
    Component::load(owner);
    owner->addModelComponents(this);
    model = owner->getScene()->getModelManager().addModel("../assets/models/backpack/backpack.obj");
}

void ModelC::reloadModel(Object *owner, const char * modelPath) {
    model = owner->getScene()->getModelManager().addModel(modelPath, model);
}

std::shared_ptr<Model> ModelC::getModel() {
    return model;
}

Component * ModelC::clone() {
    return new ModelC(*this);
}

bool ModelC::isNormalShow() {
    return showNormals;
}

void ModelC::setNormalShow(bool showNormals) {
    this->showNormals = showNormals;
}
