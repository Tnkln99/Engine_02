#ifndef ENGINE_02_SCENE_H
#define ENGINE_02_SCENE_H

#include <vector>

#include "Assets.h"
#include "Object.h"
#include "Components/MeshC.h"
#include <vector>
#include <algorithm>

#include <GLFW/glfw3.h>

class EngineCamera;

class Scene  {
private:
    std::unique_ptr<EngineCamera> camera;
    std::vector<std::unique_ptr<Object>> objects;
    std::vector<Mesh*> meshes;
    // after loading these meshes renderer will clear this vector
    std::vector<Mesh*>  meshesWaitingToBeLoad;
public:
    Scene();
    ~Scene();

    void addObject(std::unique_ptr<Object> object){
        objects.push_back(std::move(object));
    };

    EngineCamera* getCamera();
    const std::vector<std::unique_ptr<Object>> & getObjects();
    const std::vector<Mesh*> & getMeshes();
    // WTBL = waiting to be load
    std::vector<Mesh*> & getMeshesWTBL();

    void load(GLFWwindow * window);

    void update(float dt);

    void addInput(GLFWwindow * window, float deltaTime);
    void addObject();
    void addMesh(Mesh * mesh);

    Mesh * findTypeOfMesh(char typeOfMesh);
};


#endif //ENGINE_02_DefaultScene_H
