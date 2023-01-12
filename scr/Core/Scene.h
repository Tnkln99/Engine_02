#ifndef ENGINE_02_SCENE_H
#define ENGINE_02_SCENE_H

#include <vector>

#include "../Utils/Assets.h"
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
    std::vector<std::shared_ptr<Mesh>> meshes;
    // after loading these meshes renderer will clear this vector
    std::vector<Mesh*>  meshesWaitingToBeLoad;
public:
    Scene();
    ~Scene();

    void load(GLFWwindow * window);

    void addObject(Object * object){
        std::unique_ptr<Object> newObject(object);
        objects.push_back(std::move(newObject));
    };

    EngineCamera* getCamera();
    const std::vector<std::unique_ptr<Object>> & getObjects();
    const std::vector<LightC*> & getLights();
    // will add the mesh if that mesh does not already exist in the scene
    const std::vector<std::shared_ptr<Mesh>> & getMeshes();
    // WTBL = waiting to be load
    std::vector<Mesh*> & getMeshesWTBL();

    void update(float dt);

    void addInput(GLFWwindow * window, float deltaTime);
    // this if for the UI, it will simply create a new Object and this object will add itSelf to the scene
    void addObject();
    // will add the mesh to the mesh and meshWTBL vectors
    void addMesh(std::shared_ptr<Mesh> mesh);
    void addLight(LightC * light);

    std::shared_ptr<Mesh> findTypeOfMesh(char typeOfMesh); //todo: move this to a helper class, with additional mesh vector parameter
};


#endif //ENGINE_02_DefaultScene_H
