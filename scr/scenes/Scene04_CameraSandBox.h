#ifndef ENGINE_02_SCENE04_CAMERASANDBOX_H
#define ENGINE_02_SCENE04_CAMERASANDBOX_H

#include "Scene.h"
class Camera;

class Scene04_CameraSandBox : public Scene{
private:
    Camera* camera;

    glm::mat4 projMatrix = glm::mat4(1.0f);

    Shader shader;

    Mesh mesh;
    Object* object;
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
