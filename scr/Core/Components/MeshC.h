// Component to reference the Mesh
#ifndef CUBEMESH_H
#define CUBEMESH_H
#include "Component.h"
#include "../Mesh.h"
#include <memory>

class Object;

class MeshC : public Component{
private:
    Mesh* mesh;
public:
    explicit MeshC();
    ~MeshC() override;

    Mesh * getMesh();

    void load(Object * owner) override;
    Component * clone() override;
};

#endif