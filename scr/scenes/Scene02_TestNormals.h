#ifndef ENGINE_02_SCENE02_TESTNORMALS_H
#define ENGINE_02_SCENE02_TESTNORMALS_H
#include "Scene.h"
class Camera;
class Scene02_TestNormals : public Scene {
private:
    Shader shader;

    Mesh mesh;
    bool showNormals;

    Object* object;
    Camera* camera;
public:
    Scene02_TestNormals();
    ~Scene02_TestNormals() override;

    void load(GLFWwindow * window) override;
    void clean() override;

    void update() override;
    void draw() override;

    void addInput(GLFWwindow * window) override;
};


#endif //ENGINE_02_SCENE02_TESTNORMALS_H
