#ifndef RENDERER_H
#define RENDERER_H

#include "RenderComponent.h"

class Mesh;
class Object;

class MeshRenderer : public RenderComponent{
private:
    Material material;
    Mesh* mesh;
public:
    explicit MeshRenderer(Object * owner);

    //if there is already a material this methode will change it with the new input
    void setMaterial(const Material & material);
    //add mesh this method should find mesh component from the owner if exists
    void setMesh(Mesh * mesh);

    Material & getMaterial() override;
    Mesh * getMesh() override;
};

#endif