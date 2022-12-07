#ifndef ENGINE_02_SCENE_H
#define ENGINE_02_SCENE_H

#include <vector>

#include "Assets.h"
#include "Object.h"
#include "GLFW/glfw3.h"
#include "Mesh.h"
#include <vector>

class EngineCamera;

class Scene{
public:
    virtual ~Scene() = default;

    void addObject(Object * object){
        objects.emplace_back(object);
    };

    virtual void load(GLFWwindow * window) = 0;

    virtual void update(float dt) = 0;

    virtual void addInput(GLFWwindow *window, float deltaTime) = 0;

    EngineCamera * camera;
    std::vector<Object*> objects;
};

#endif //ENGINE_02_SCENE_H
