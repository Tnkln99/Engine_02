#include "ModelManager.h"

std::shared_ptr<Model> ModelManager::addModel(const char * modelPath, std::shared_ptr<Model> oldModel) {
    if(oldModel != nullptr) {
        if (oldModel.use_count() <= 3) {
            if (modelPath == oldModel->getNameOfModel()){ return oldModel; }
            deleteModel(oldModel->getPath());
        }
    }

    // checks if that mesh already in game if its not, will create it and return the mesh that has been created
    if (modelsInGame.find(modelPath) != modelsInGame.end())
    {
        return modelsInGame[modelPath];
    }
    else
    {
        std::shared_ptr<Model> newModel = std::make_shared<Model>(modelPath);
        modelWaitingToBeLoaded.push_back(newModel);
        modelsInGame[modelPath] = newModel;
        return newModel;
    }
}

void ModelManager::deleteModel(std::string modelPath) {
    modelsInGame.erase(modelPath);
}

void ModelManager::notifyLoaded() {
    modelWaitingToBeLoaded.clear();
}

std::vector<std::shared_ptr<Model>> ModelManager::getModelsWaitingToBeLoaded() {
    return modelWaitingToBeLoaded;
}

const std::map<std::string, std::shared_ptr<Model>> &ModelManager::getAllModels() {
    return modelsInGame;
}


