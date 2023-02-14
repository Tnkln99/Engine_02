#include "MeshC.h"
#include "../Scene.h"


MeshC::MeshC() : Component("mesh"){

}

MeshC::~MeshC() {

}

void MeshC::load(Object *owner) {
    Component::load(owner);
    if(owner->getScene()->findMesh('c') != nullptr){
        mesh = owner->getScene()->findMesh('c');
    }
    else {
        mesh = std::make_shared<Mesh>('c');
        owner->getScene()->addMesh(mesh);
    }
}

void MeshC::reloadMesh(Object *owner, char c) {
    if(owner->getScene()->findMesh(c) != nullptr){
        mesh = owner->getScene()->findMesh(c);
    }
    else {
        mesh = std::make_shared<Mesh>(c);
        owner->getScene()->addMesh(mesh);
    }
}

Component * MeshC::clone() {
    return new MeshC(*this);
}

std::shared_ptr<Mesh> MeshC::getMesh() {
    return mesh;
}
