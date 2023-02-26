// Component to reference the Mesh
#ifndef CUBEMESH_H
#define CUBEMESH_H
#include "Component.h"
#include "../../Graphics/BackEnd/Model.h"
#include <memory>

class Object;

class ModelC : public Component{
private:
    std::shared_ptr<Model> model;
public:
    explicit ModelC();
    ~ModelC() override;

    std::shared_ptr<Model> getModel();

    void load(Object * owner) override;
    void reloadModel(Object * owner,const char * modelPath);
    Component * clone() override;
};

#endif