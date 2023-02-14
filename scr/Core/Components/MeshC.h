// Component to reference the Mesh
#ifndef CUBEMESH_H
#define CUBEMESH_H
#include "Component.h"
#include "../Embedded Components/Mesh.h"
#include <memory>

class Object;

class MeshC : public Component{
private:
    std::shared_ptr<Mesh> mesh;
public:
    explicit MeshC();
    ~MeshC() override;

    std::shared_ptr<Mesh> getMesh();

    void load(Object * owner) override;
    void reloadMesh(Object * owner, char c);
    Component * clone() override;
};

#endif