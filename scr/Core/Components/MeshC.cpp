#include "MeshC.h"
#include "../Scene.h"


MeshC::MeshC() : Component("mesh"){

}

MeshC::~MeshC() {

}

void MeshC::load(Object *owner) {
    Component::load(owner);
    mesh = owner->getScene()->getMeshManager().addMesh("Cube");
}

void MeshC::reloadMesh(Object *owner, const std::string & meshName) {
    mesh = owner->getScene()->getMeshManager().addMesh(meshName, mesh);
}

Component * MeshC::clone() {
    return new MeshC(*this);
}

std::shared_ptr<Mesh> MeshC::getMesh() {
    return mesh;
}
