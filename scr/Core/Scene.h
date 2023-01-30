#ifndef ENGINE_02_SCENE_H
#define ENGINE_02_SCENE_H

#include <vector>

#include "../Utils/Assets.h"
#include "Object.h"
#include "Components/MeshC.h"
#include "Components/LightC.h"
#include "Components/MeshRendererC.h"
#include <vector>
#include <algorithm>

#include "GLFW/glfw3.h"

class EngineCamera;

class Scene  {
private:
    std::unique_ptr<EngineCamera> camera;

    std::vector<std::unique_ptr<Object>> objects;
    std::vector<LightC*> lights;
    // after loading these meshes renderer will clear this vector
    std::vector<Mesh*>  meshesWaitingToBeLoad;
public:
    Scene();
    ~Scene();

    void load(GLFWwindow * window, float sceneWidth, float sceneHeight);

    void addObject(Object * object){
        std::unique_ptr<Object> newObject(object);
        objects.push_back(std::move(newObject));
    };

    EngineCamera* getCamera();
    const std::vector<std::unique_ptr<Object>> & getObjects();
    const std::vector<LightC*> & getLights();
    // WTBL = waiting to be load
    std::vector<Mesh*> & getMeshesWTBL();

    void update(float dt);

    void addInput(GLFWwindow * window, float deltaTime);
    // this if for the UI, it will simply create a new Object and this object will add itSelf to the scene
    void addObject();
    // will add the mesh to the mesh and meshWTBL vectors
    void addMesh(std::shared_ptr<Mesh> mesh);
    void addLight(LightC * light);

    // will send the type of mesh needed if it already exists in the scene
    std::shared_ptr<Mesh> findMesh(char typeOfMesh);
};


#endif //ENGINE_02_DefaultScene_H
