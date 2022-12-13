#include "MeshC.h"
#include "../Scene.h"


MeshC::MeshC() : Component("mesh"){

}

MeshC::~MeshC() {
    delete mesh;
}

void MeshC::load(Object *owner) {
    Component::load(owner);
    if(owner->getScene()->findTypeOfMesh('i') != nullptr){
        mesh = owner->getScene()->findTypeOfMesh('i');
    }
    else {
        mesh = new Mesh;
    }
    owner->getScene()->addMesh(std::move(mesh));
}

Component * MeshC::clone() {
    return new MeshC(*this);
}

Mesh * MeshC::getMesh() {
    return mesh;
}
