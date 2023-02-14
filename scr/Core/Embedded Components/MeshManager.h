#ifndef ENGINE_02_MESHMANAGER_H
#define ENGINE_02_MESHMANAGER_H

#include "Mesh.h"
#include <memory>
#include <map>
#include <iostream>

class MeshManager {
private:
    std::map<std::string, std::shared_ptr<Mesh>> meshesInGame;
    std::vector<std::shared_ptr<Mesh>> meshWaitingToBeLoaded;
public:
    std::shared_ptr<Mesh> addMesh(const std::string & newMeshName, std::shared_ptr<Mesh> oldMesh = nullptr);
    void deleteMesh(std::string meshName);

    void notifyLoaded();

    std::vector<std::shared_ptr<Mesh>> getMeshesWaitingToBeLoaded();
    const std::map<std::string, std::shared_ptr<Mesh>> & getAllMeshes();
};


#endif //ENGINE_02_MESHMANAGER_H
