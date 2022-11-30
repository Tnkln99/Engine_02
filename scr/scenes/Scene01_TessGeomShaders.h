#ifndef ENGINE_02_SCENE01_TESSGEOMSHADERS_H
#define ENGINE_02_SCENE01_TESSGEOMSHADERS_H

#include "Scene.h"

class Scene01_TessGeomShaders : public Scene {
private:
    glm::mat4 projMatrix = glm::mat4(1.0f);
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    Shader shader;

    Mesh mesh;

    RenderableObject* object;
    Camera* camera;
    //Object* object2;

    GLfloat innerTess {0.0f};
    GLfloat outerTess {0.0f};
public:
    Scene01_TessGeomShaders();
    ~Scene01_TessGeomShaders() override;

    void load(GLFWwindow * window) override;
    void clean() override;

    void update(float dt) override;
    void draw() override;

    void addInput(GLFWwindow * window, float deltaTime) override;
};


#endif //ENGINE_02_SCENE01_TESSGEOMSHADERS_H
