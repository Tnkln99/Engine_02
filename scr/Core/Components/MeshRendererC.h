#ifndef RENDERER_H
#define RENDERER_H

#include "Component.h"
#include "../Embedded Components/Material.h"

class MeshC;
class Object;

class MeshRendererC : public Component{
private:
    Material material;
    MeshC* mesh;

    int renderOrder = 0;
public:
    explicit MeshRendererC();
    ~MeshRendererC() override;

    //if there is already a material this methode will change it with the new input
    void setMaterial(const Material & material);

    //add mesh this method should find mesh component from the owner if exists
    void setMeshC(MeshC * mesh);

    Material & getMaterial();
    MeshC * getMeshC();
    [[nodiscard]] int genRenderOrder() const;

    void load(Object * owner) override;
    Component * clone() override;
};

#endif