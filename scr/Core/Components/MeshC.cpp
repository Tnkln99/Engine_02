#include "MeshC.h"
#include "../Scene.h"


MeshC::MeshC() : Component("mesh"){

}

MeshC::~MeshC() {

}

void MeshC::load(Object *owner) {
    Component::load(owner);
    if(owner->getScene()->findTypeOfMesh('t') != nullptr){
        mesh = owner->getScene()->findTypeOfMesh('t');
    }
    else {
        mesh = new Mesh;
    }
    owner->getScene()->addMesh(mesh);
}

Component * MeshC::clone() {
    return new MeshC(*this);
}

Mesh * MeshC::getMesh() {
    return mesh;
}
