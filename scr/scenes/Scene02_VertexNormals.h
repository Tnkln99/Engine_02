#ifndef ENGINE_02_SCENE02_VERTEXNORMALS_H
#define ENGINE_02_SCENE02_VERTEXNORMALS_H
#include "Scene.h"

class Scene02_VertexNormals : public Scene {
private:
    glm::mat4 projMatrix = glm::mat4(1.0f);
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    Shader shader;

    Mesh mesh;

    Object* object;
public:
    Scene02_VertexNormals();
    ~Scene02_VertexNormals() override;

    void load(float windowWidth, float windowHeight) override;
    void clean() override;

    void update() override;
    void draw() override;
};


#endif //ENGINE_02_SCENE02_VERTEXNORMALS_H
