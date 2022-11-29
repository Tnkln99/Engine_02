#ifndef ENGINE_02_SCENE04_CAMERASANDBOX_H
#define ENGINE_02_SCENE04_CAMERASANDBOX_H

#include "Scene.h"

class Scene04_CameraSandBox : public Scene{
private:
    Camera* camera;

    Shader shader;

    Mesh mesh;

    Object* object;
    Object* object2;
public:
    Scene04_CameraSandBox();
    ~Scene04_CameraSandBox() override;

    void load(GLFWwindow * window) override;
    void clean() override;

    void update() override;
    void draw() override;

    void addInput(GLFWwindow * window) override;
};


#endif //ENGINE_02_SCENE04_CAMERASANDBOX_H
