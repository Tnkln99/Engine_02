#ifndef ENGINE_02_SCENE_H
#define ENGINE_02_SCENE_H

#include <vector>

#include "Assets.h"
#include "Object.h"
#include "Components/Mesh.h"
#include <vector>

#include <GLFW/glfw3.h>

class EngineCamera;

class Scene  {
private:
    EngineCamera * camera;
    std::vector<Object*> objects;
    std::vector<Mesh*> meshes;
public:
    Scene();
    ~Scene();

    void addObject(Object * object){
        objects.emplace_back(object);
    };

    EngineCamera * getCamera();
    const std::vector<Object*> & getObjects();
    const std::vector<Mesh*> & getMeshes();

    void load(GLFWwindow * window);

    void update(float dt);

    void addInput(GLFWwindow * window, float deltaTime);
    void addObject();
    void addMesh(Mesh * mesh);

    Mesh * findTypeOfMesh(char typeOfMesh);
};


#endif //ENGINE_02_DefaultScene_H
