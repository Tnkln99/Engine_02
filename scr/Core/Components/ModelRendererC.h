#ifndef RENDERER_H
#define RENDERER_H

#include "Component.h"
#include "../../Graphics/BackEnd/Material.h"

class ModelC;
class Object;

class ModelRendererC : public Component{
private:
    Material material;
    ModelC* mesh;

    int renderOrder = 0;
public:
    explicit ModelRendererC();
    ~ModelRendererC() override;

    //if there is already a material this methode will change it with the new input
    void setMaterial(const Material & material);

    //add mesh this method should find mesh component from the owner if exists
    void setModelC(ModelC * mesh);

    Material & getMaterial();
    ModelC * getModelC();
    [[nodiscard]] int getRenderOrder() const;

    void load(Object * owner) override;
    Component * clone() override;
};

#endif