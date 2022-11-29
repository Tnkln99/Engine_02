#ifndef ENGINE_02_SCENE05_LIGHTSANDBOX_H
#define ENGINE_02_SCENE05_LIGHTSANDBOX_H

#include "Scene.h"

class Scene05_LightSandBox : public Scene{
private:
    Shader shader;

    Mesh mesh;

    RenderableObject* object;
    Light* light;

    Camera* camera;
public:
    Scene05_LightSandBox();
    ~Scene05_LightSandBox() override;

    void load(GLFWwindow * window) override;
    void clean() override;

    void update() override;
    void draw() override;

    void addInput(GLFWwindow * window) override;
};


#endif //ENGINE_02_SCENE05_LIGHTSANDBOX_H
