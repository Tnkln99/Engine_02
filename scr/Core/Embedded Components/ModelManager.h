#ifndef ENGINE_02_MODELMANAGER_H
#define ENGINE_02_MODELMANAGER_H

#include "../../Graphics/BackEnd/Mesh.h"
#include <memory>
#include <map>
#include <iostream>
#include "../../Graphics/BackEnd/Model.h"
class ModelManager {
private:
    std::map<std::string, std::shared_ptr<Model>> modelsInGame;
    std::vector<std::shared_ptr<Model>> modelWaitingToBeLoaded;
public:
    std::shared_ptr<Model> addModel(char * modelPath, std::shared_ptr<Model> oldModel = nullptr);
    void deleteModel(std::string modelName);

    void notifyLoaded();

    std::vector<std::shared_ptr<Model>> getModelsWaitingToBeLoaded();
    const std::map<std::string, std::shared_ptr<Model>> & getAllModels();
};


#endif //ENGINE_02_MODELMANAGER_H
