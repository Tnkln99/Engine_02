#include "MeshManager.h"

std::shared_ptr<Mesh> MeshManager::addMesh(const std::string & newMeshName, std::shared_ptr<Mesh> oldMesh) {
    if(oldMesh != nullptr) {
        if (oldMesh.use_count() <= 3) {
            if (newMeshName == oldMesh->getNameOfMesh()){return oldMesh;}
            deleteMesh(oldMesh->getNameOfMesh());
        }
    }

    // checks if that mesh already in game if its not, will create it and return the mesh that has been created
    if (meshesInGame.find(newMeshName) != meshesInGame.end())
    {
        return meshesInGame[newMeshName];
    }
    else
    {
        std::shared_ptr<Mesh> newMesh = std::make_shared<Mesh>(newMeshName);
        meshWaitingToBeLoaded.push_back(newMesh);
        meshesInGame[newMeshName] = newMesh;
        return newMesh;
    }
}

void MeshManager::deleteMesh(std::string meshName) {
    meshesInGame.erase(meshName);
}

void MeshManager::notifyLoaded() {
    meshWaitingToBeLoaded.clear();
}

std::vector<std::shared_ptr<Mesh>> MeshManager::getMeshesWaitingToBeLoaded() {
    return meshWaitingToBeLoaded;
}

const std::map<std::string, std::shared_ptr<Mesh>> &MeshManager::getAllMeshes() {
    return meshesInGame;
}


