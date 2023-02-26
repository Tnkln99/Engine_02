#include "Renderer.h"
#include "../../Core/EngineCamera.h"
#include "Assets.h"


void Renderer::load() {
    shadowMapShader = Assets::loadShaderFromFile("../assets/shaders/shadowMap.vert", "../assets/shaders/shadowMap.frag", "", "", "");
    normalsShader = Assets::loadShaderFromFile("../assets/shaders/normals.vert", "../assets/shaders/normals.frag", "", "", "../assets/shaders/normals.geom");
    lightsShader = Assets::loadShaderFromFile("../assets/shaders/light.vert", "../assets/shaders/light.frag", "", "", "");
    skyBox.load();
}


void Renderer::renderToShadowMap(Scene &scene) {
    if(scene.getModelManager().getModelsWaitingToBeLoaded().size() != 0){
        for(auto & model : scene.getModelManager().getModelsWaitingToBeLoaded()){
            for (auto & mesh : model->getMeshes()){
                mesh.load();
            }
        }
        scene.getModelManager().notifyLoaded();
    }

    shadowMapShader.use();
    for (auto &light: scene.getLights()) {
        light->shadowMap.bind(0.07f, 0.13f, 0.17f);
        shadowMapShader.setMatrix4("lightSpaceMatrix", light->getSpaceMatrix());
        for (auto &object: scene.getObjects()) {
            for (auto &modelC: object->getModelComponents()) {
                for(auto & mesh : modelC->getModel()->getMeshes()) {
                    shadowMapShader.setMatrix4("modelMatrix", modelC->getOwner()->getTransform().getModelMatrix());
                    drawMesh(&mesh);
                }
            }
        }

        light->shadowMap.unbind(1920,1080);
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
                mesh.load();
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
                shaderOnUse->setMatrix4("projMatrix", scene.getCamera()->getProjMatrix());
                shaderOnUse->setMatrix4("viewMatrix", scene.getCamera()->getViewMatrix());
                shaderOnUse->setMatrix4("modelMatrix", modelC->getOwner()->getTransform().getModelMatrix());

                shaderOnUse->setVector3f("viewPos", scene.getCamera()->getTransform().getPosition());
                shaderOnUse->setVector3f("ambient", mesh.material.getAmbient());
                shaderOnUse->setVector3f("diffuse", mesh.material.getDiffuse());
                shaderOnUse->setVector3f("specular", mesh.material.getSpecular());
                shaderOnUse->setFloat("shininess", mesh.material.getShininess());

                std::vector<Texture> textures = mesh.getTextures();
                unsigned int diffuseNr = 1;
                unsigned int specularNr = 1;
                int diffuseTextureUsing = 0;
                int specularTextureUsing = 0;
                for (unsigned int i = 0; i < textures.size(); i++) {
                    glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
                    // retrieve texture number (the N in diffuse_textureN)
                    std::string number;
                    std::string name = textures[i].type;
                    if (name == "texture_diffuse") {
                        diffuseTextureUsing = 1;
                        number = std::to_string(diffuseNr++);
                    }
                    else if (name == "texture_specular") {
                        specularTextureUsing = 1;
                        number = std::to_string(specularNr++);
                    }
                    shaderOnUse->setInteger((name + number).c_str(), i);
                    glBindTexture(GL_TEXTURE_2D, textures[i].id);
                }
                shaderOnUse->setInteger("diffuseTextureUsing",diffuseTextureUsing);
                shaderOnUse->setInteger("specularTextureUsing",specularTextureUsing);
                shaderOnUse->setInteger("lightCount", scene.getLights().size());
                int lightNo = 0;
                for(auto & light : scene.getLights()) {
                    std::string stringLightNoPos = "light[" + std::to_string(lightNo) + "].position";
                    std::string stringLightColor = "light[" + std::to_string(lightNo) + "].color";
                    std::string stringLightShadowMap = "light[" + std::to_string(lightNo) + "].shadowMap";
                    std::string stringLightSpaceMatrix= "lightSpaceMatrix[" + std::to_string(lightNo) + "]";

                    shaderOnUse->setMatrix4(stringLightSpaceMatrix.c_str(), light->getSpaceMatrix());
                    shaderOnUse->setVector3f(stringLightNoPos.c_str(),
                                             light->getOwner()->getTransform().getPosition());
                    shaderOnUse->setVector3f(stringLightColor.c_str(), light->getColor());

                    glActiveTexture(GL_TEXTURE0+2+lightNo);
                    shaderOnUse->setInteger(stringLightShadowMap.c_str(), 2+lightNo);
                    glBindTexture(GL_TEXTURE_2D, *light->shadowMap.getTexture());


                    lightNo++;
                }

                drawMesh(&mesh);

                // drawing edit mode mesh
                for(auto & light : scene.getLights()) {
                    lightsShader.use();
                    lightsShader.setMatrix4("projMatrix", scene.getCamera()->getProjMatrix());
                    lightsShader.setMatrix4("viewMatrix", scene.getCamera()->getViewMatrix());
                    lightsShader.setMatrix4("modelMatrix", light->getOwner()->getTransform().getModelMatrix());
                    for (auto &lightMesh: light->editModel->getMeshes()) {
                        drawMesh(&lightMesh);
                    }
                }

                // ---------------------------------------------------- DEBUG ----------------------------------------------------------
                if(modelC->isNormalShow()) {
                    normalsShader.use();
                    normalsShader.setMatrix4("proj_matrix", scene.getCamera()->getProjMatrix());
                    normalsShader.setMatrix4("view_matrix", scene.getCamera()->getViewMatrix());
                    normalsShader.setMatrix4("transform", modelC->getOwner()->getTransform().getModelMatrix());
                    drawMesh(&mesh);
                }

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




