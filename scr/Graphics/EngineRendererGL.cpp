#include "EngineRendererGL.h"
#include "../Core/EngineCamera.h"
#include "../Core/Components/RenderComponent.h"

void EngineRendererGL::loadMesh(Mesh *mesh){
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

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void EngineRendererGL::forwardRender(Scene & scene) {
    for(auto & object : scene.getObjects()){
        for(auto & component : object->getRenderComponents()){
            Assets::getShader(component->getMaterial().getShaderId()).use();
            Assets::getShader(component->getMaterial().getShaderId()).setMatrix4("proj_matrix", scene.getCamera()->getProjMatrix());
            Assets::getShader(component->getMaterial().getShaderId()).setMatrix4("view_matrix", scene.getCamera()->getViewMatrix());
            Assets::getShader(component->getMaterial().getShaderId()).setMatrix4("transform", component->getOwner()->getTransform().getMoveMatrix());

            Assets::getShader(component->getMaterial().getShaderId()).setVector3f("viewPos", scene.getCamera()->getTransform().getPosition());

            Assets::getShader(component->getMaterial().getShaderId()).setVector3f("material.ambient", component->getMaterial().getAmbient());
            Assets::getShader(component->getMaterial().getShaderId()).setVector3f("material.diffuse", component->getMaterial().getDiffuse());
            Assets::getShader(component->getMaterial().getShaderId()).setVector3f("material.specular", component->getMaterial().getDiffuse());
            Assets::getShader(component->getMaterial().getShaderId()).setFloat("material.shininess", component->getMaterial().getShininess());

            int lightNo = 0;
            for(auto & light : scene.getLights()) {
                //component->getMaterial().getShader().setInteger("light_count",
                //                                                 scene.getLights().size());

                std::string stringLightNoPos = "light[" + std::to_string(lightNo) + "].position";
                std::string stringLightAmbient = "light[" + std::to_string(lightNo) + "].ambient";
                std::string stringLightNoDiffuse = "light[" + std::to_string(lightNo) + "].diffuse";
                std::string stringLightNoSpecular = "light[" + std::to_string(lightNo) + "].specular";

                Assets::getShader(component->getMaterial().getShaderId()).setVector3f(stringLightNoPos.c_str(),
                                                                 light->getOwner()->getTransform().getPosition());
                Assets::getShader(component->getMaterial().getShaderId()).setVector3f(stringLightAmbient.c_str(), light->getAmbientColor());
                Assets::getShader(component->getMaterial().getShaderId()).setVector3f(stringLightNoDiffuse.c_str(), light->getDiffuseColor());
                Assets::getShader(component->getMaterial().getShaderId()).setVector3f(stringLightNoSpecular.c_str(), light->getSpecular());
                lightNo++;
            }

            if(scene.getMeshesWTBL().size() != 0){
                for(auto & mesh : scene.getMeshesWTBL()){
                    loadMesh(mesh);
                }
                scene.getMeshesWTBL().clear();
            }
            drawMesh(component->getMeshC()->getMesh().get());
        }
    }

}

void EngineRendererGL::drawMesh(Mesh *mesh) {
    glBindVertexArray(mesh->getId());
    glDrawElements(GL_TRIANGLES , mesh->getIndices().size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void EngineRendererGL::cleanRenderer() {
    for(auto & vao : loadedMeshIds){
        glDeleteVertexArrays(1, &vao);
    }
}


