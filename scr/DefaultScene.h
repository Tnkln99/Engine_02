#ifndef ENGINE_02_DEFAULTSCENE_H
#define ENGINE_02_DEFAULTSCENE_H

#include "Scene.h"
class MeshRenderer;
class Mesh;

class DefaultScene : public Scene {
private:
    Object* mainObject;
    Mesh* mesh;
    MeshRenderer* meshRenderer;
public:
    DefaultScene();
    ~DefaultScene() override;

    void load(GLFWwindow * window) override;

    void update(float dt) override;

    void addInput(GLFWwindow * window, float deltaTime) override;
};


#endif //ENGINE_02_DefaultScene_H
