#ifndef ENGINE_02_SCENE_H
#define ENGINE_02_SCENE_H

#include <vector>

#include <glad/glad.h>
#include "../Assets.h"
#include "GLFW/glfw3.h"
#include "../Mesh.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

class Object;

class Scene{
public:
    virtual ~Scene() = default;

    virtual void load(GLFWwindow * window) = 0;
    virtual void clean() = 0;

    virtual void update() = 0;
    virtual void draw() = 0;

    virtual void addInput(GLFWwindow *window) = 0;
};

#endif //ENGINE_02_SCENE_H
