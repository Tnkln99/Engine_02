#ifndef ENGINE_02_SCENE_H
#define ENGINE_02_SCENE_H

#include <vector>

#include "Object.h"
#include "Components/MeshC.h"
#include "Components/LightC.h"
#include "Components/MeshRendererC.h"
#include "Embedded Components/MeshManager.h"
#include <vector>
#include <algorithm>
#include <map>

#include "GLFW/glfw3.h"

class EngineCamera;

class Scene  {
private:
    std::unique_ptr<EngineCamera> camera;

    std::vector<std::unique_ptr<Object>> objects;
    std::vector<LightC*> lights;

    MeshManager meshManager;
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

    MeshManager & getMeshManager();

    void update(float dt);

    void addInput(GLFWwindow * window, float deltaTime);
    // this if for the UI, it will simply create a new Object and this object will add itSelf to the scene
    void addObject();

    void addLight(LightC * light);
};


#endif //ENGINE_02_DefaultScene_H
