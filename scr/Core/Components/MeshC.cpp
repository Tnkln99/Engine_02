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
        mesh = new Mesh('t');
    }
    owner->getScene()->addMesh(mesh);
}

void MeshC::reloadMesh(Object *owner, char c) {
    if(owner->getScene()->findTypeOfMesh(c) != nullptr){
        mesh = owner->getScene()->findTypeOfMesh(c);
    }
    else {
        mesh = new Mesh(c);
    }
    owner->getScene()->addMesh(mesh);
}

Component * MeshC::clone() {
    return new MeshC(*this);
}

Mesh * MeshC::getMesh() {
    return mesh;
}

void MeshC::setMesh() {

}
