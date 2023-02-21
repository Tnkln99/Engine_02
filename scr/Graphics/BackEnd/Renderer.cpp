#include "Renderer.h"
#include "../../Core/EngineCamera.h"
#include "Assets.h"
#include <stddef.h>     /* offsetof */


void Renderer::load() {
    shadowMapShader = Assets::loadShaderFromFile("../assets/shaders/shadowMap.vert", "../assets/shaders/shadowMap.frag", "", "", "");
    debugNormals = Assets::loadShaderFromFile("../assets/shaders/debug/normalsDebug.vert", "../assets/shaders/debug/normalsDebug.frag", "", "", "../assets/shaders/debug/normalsDebug.geom");
    skyBox.load();
}

void Renderer::loadMesh(Mesh *mesh){
    GLuint EBO, VBO;
    // Generate the VAO and VBO with only 1 object each
    glGenVertexArrays(1, &mesh->getId());
    loadedMeshIds.emplace_back(mesh->getId());
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Make the VAO the current Vertex Array Object by binding it
    glBindVertexArray(mesh->getId());

    // Bind the VBO_N specifying it's a GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Introduce the positions into the VBO
    glBufferData(GL_ARRAY_BUFFER, mesh->getVertices().size() * sizeof(Vertex), mesh->getVertices().data(), GL_STATIC_DRAW);


    // Bind the EBO specifying it's a GL_ELEMENT_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // Introduce the indices into the EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndices().size() * sizeof(GLuint), mesh->getIndices().data(), GL_STATIC_DRAW);


    // Setup vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

    glBindVertexArray(0);
}


void Renderer::renderToShadowMap(Scene &scene) {
    if(scene.getModelManager().getModelsWaitingToBeLoaded().size() != 0){
        for(auto & model : scene.getModelManager().getModelsWaitingToBeLoaded()){
            for (auto & mesh : model->getMeshes()){
                loadMesh(&mesh);
            }
        }
        scene.getModelManager().notifyLoaded();
    }
    shadowMapShader.use();
    for (auto &object: scene.getObjects()) {
        for (auto &modelC: object->getModelComponents()) {
            for(auto & mesh : modelC->getModel()->getMeshes()) {
                shadowMapShader.setMatrix4("model", modelC->getOwner()->getTransform().getMoveMatrix());

                for (auto &light: scene.getLights()) {
                    shadowMapShader.setMatrix4("lightSpaceMatrix", light->getSpaceMatrix());
                }


                drawMesh(&mesh);
            }
        }
    }
}

void Renderer::renderScene(Scene & scene, unsigned int depthMap) {
    if (renderMode == RenderMode::POINT)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }
    else if (renderMode == RenderMode::LINE)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }


    if(scene.getModelManager().getModelsWaitingToBeLoaded().size() != 0){
        for(auto & model : scene.getModelManager().getModelsWaitingToBeLoaded()){
            for (auto & mesh : model->getMeshes()){
                loadMesh(&mesh);
            }
        }
        scene.getModelManager().notifyLoaded();
    }

    for(auto & object : scene.getObjects()) {
        for (auto & modelC : object->getModelComponents()){
            for (auto & mesh : modelC->getModel()->getMeshes()){
                Shader* shaderOnUse = mesh.material.shader;
                shaderOnUse->use();
                //glActiveTexture(GL_TEXTURE0);
                //glBindTexture(GL_TEXTURE_2D, depthMap);
                shaderOnUse->setMatrix4("proj_matrix", scene.getCamera()->getProjMatrix());
                shaderOnUse->setMatrix4("view_matrix", scene.getCamera()->getViewMatrix());
                shaderOnUse->setMatrix4("transform", modelC->getOwner()->getTransform().getMoveMatrix());

                shaderOnUse->setVector3f("viewPos", scene.getCamera()->getTransform().getPosition());
                shaderOnUse->setVector3f("ambient", mesh.material.getAmbient());
                shaderOnUse->setVector3f("diffuse", mesh.material.getDiffuse());
                shaderOnUse->setVector3f("specular", mesh.material.getSpecular());
                shaderOnUse->setFloat("shininess", mesh.material.getShininess());
                int lightNo = 0;
                for(auto & light : scene.getLights()) {
                    std::string stringLightNoPos = "light[" + std::to_string(lightNo) + "].position";
                    std::string stringLightColor = "light[" + std::to_string(lightNo) + "].color";

                    shaderOnUse->setMatrix4("lightSpaceMatrix", light->getSpaceMatrix());
                    shaderOnUse->setVector3f(stringLightNoPos.c_str(),
                                            light->getOwner()->getTransform().getPosition());
                    shaderOnUse->setVector3f(stringLightColor.c_str(), light->getColor());
                    lightNo++;
                }
                std::vector<Texture> textures = mesh.getTextures();
                unsigned int diffuseNr = 1;
                unsigned int specularNr = 1;
                for (unsigned int i = 0; i < textures.size(); i++) {
                    glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
                    // retrieve texture number (the N in diffuse_textureN)
                    std::string number;
                    std::string name = textures[i].type;
                    if (name == "texture_diffuse") {
                        shaderOnUse->setInteger("diffuseTextureUsing",1);
                        number = std::to_string(diffuseNr++);
                    }
                    else if (name == "texture_specular") {
                        shaderOnUse->setInteger("specularTextureUsing",1);
                        number = std::to_string(specularNr++);
                    }

                    shaderOnUse->setInteger((name + number).c_str(), i);
                    glBindTexture(GL_TEXTURE_2D, textures[i].id);
                }
                glActiveTexture(GL_TEXTURE0+2);
                shaderOnUse->setInteger("shadowMap", 2);
                glBindTexture(GL_TEXTURE_2D, depthMap);


                drawMesh(&mesh);
                // ---------------------------------------------------- DEBUG ----------------------------------------------------------
                /*debugNormals.use();
                debugNormals.setMatrix4("proj_matrix", scene.getCamera()->getProjMatrix());
                debugNormals.setMatrix4("view_matrix", scene.getCamera()->getViewMatrix());
                debugNormals.setMatrix4("transform", component->getOwner()->getTransform().getMoveMatrix());
                drawMesh(&mesh);*/
            }
        }
    }
    glm::mat4 view = glm::mat4(glm::mat3(scene.getCamera()->getViewMatrix()));
    skyBox.renderToSkyBox(view, scene.getCamera()->getProjMatrix());
}

void Renderer::drawMesh(Mesh *mesh) {
    glBindVertexArray(mesh->getId());
    glDrawElements(GL_TRIANGLES , mesh->getIndices().size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Renderer::setRenderMode(int mode){
    switch (mode) {
        case 1:
            renderMode = RenderMode::FILL;
            break;
        case 2:
            renderMode = RenderMode::LINE;
            break;
        case 3:
            renderMode = RenderMode::POINT;
            break;
        default:
            renderMode = RenderMode::FILL;
            break;
    }
}

void Renderer::cleanRenderer() {
    for(auto & vao : loadedMeshIds){
        glDeleteVertexArrays(1, &vao);
    }
}




