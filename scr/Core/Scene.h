#ifndef ENGINE_02_SCENE_H
#define ENGINE_02_SCENE_H

#include <vector>

#include "../Assets/Assets.h"
#include "Object.h"
#include "Components/MeshC.h"
#include "Components/LightC.h"
#include <vector>
#include <algorithm>

#include "GLFW/glfw3.h"

class EngineCamera;

class Scene  {
private:
    std::unique_ptr<EngineCamera> camera;

    std::vector<std::unique_ptr<Object>> objects;
    std::vector<LightC*> lights;
    // todo: convert meshes to shared pointer to be able to delete them when nobody uses them
    std::vector<Mesh*> meshes;
    // after loading these meshes renderer will clear this vector
    std::vector<Mesh*>  meshesWaitingToBeLoad;
public:
    Scene();
    ~Scene();

    void addObject(Object * object){
        std::unique_ptr<Object> newObject(object);
        objects.push_back(std::move(newObject));
    };

    EngineCamera* getCamera();
    const std::vector<std::unique_ptr<Object>> & getObjects();
    const std::vector<LightC*> & getLights();
    const std::vector<Mesh*> & getMeshes();
    // WTBL = waiting to be load
    std::vector<Mesh*> & getMeshesWTBL();

    void load(GLFWwindow * window);

    void update(float dt);

    void addInput(GLFWwindow * window, float deltaTime);
    void addObject();
    // will add the mesh to the mesh and meshWTBL vectors
    void addMesh(Mesh * mesh);
    void addLight(LightC * light);

    Mesh * findTypeOfMesh(char typeOfMesh);
};


#endif //ENGINE_02_DefaultScene_H
