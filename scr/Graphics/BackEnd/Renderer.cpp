#include "Renderer.h"
#include "../../Core/EngineCamera.h"


void Renderer::load() {
    shadowMapShader = Assets::loadShaderFromFile("../assets/shaders/shadowMap.vert", "../assets/shaders/shadowMap.frag", "", "", "");
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

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Renderer::forwardRender(Scene & scene) {
    if (renderMode == RenderMode::POINT)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }
    else if (renderMode == RenderMode::LINE)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else if (renderMode == RenderMode::FILL)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    for(auto & object : scene.getObjects()){
        for(auto & component : object->getRenderComponents()){
            Shader shaderOnUse = Assets::getShader(component->getMaterial().getShaderId());
            shaderOnUse.use();
            shaderOnUse.setInteger("shadowMap",1);
            shaderOnUse.setMatrix4("proj_matrix", scene.getCamera()->getProjMatrix());
            shaderOnUse.setMatrix4("view_matrix", scene.getCamera()->getViewMatrix());
            shaderOnUse.setMatrix4("transform", component->getOwner()->getTransform().getMoveMatrix());

            shaderOnUse.setVector3f("viewPos", scene.getCamera()->getTransform().getPosition());

            shaderOnUse.setVector3f("material.ambient", component->getMaterial().getAmbient());
            shaderOnUse.setVector3f("material.diffuse", component->getMaterial().getDiffuse());
            shaderOnUse.setVector3f("material.specular", component->getMaterial().getDiffuse());
            shaderOnUse.setFloat("material.shininess", component->getMaterial().getShininess());

            int lightNo = 0;
            for(auto & light : scene.getLights()) {
                //component->getMaterial().getShader().setInteger("light_count",
                //                                                 scene.getLights().size());

                std::string stringLightNoPos = "light[" + std::to_string(lightNo) + "].position";
                std::string stringLightAmbient = "light[" + std::to_string(lightNo) + "].ambient";
                std::string stringLightNoDiffuse = "light[" + std::to_string(lightNo) + "].diffuse";
                std::string stringLightNoSpecular = "light[" + std::to_string(lightNo) + "].specular";

                shaderOnUse.setVector3f(stringLightNoPos.c_str(),
                                                                 light->getOwner()->getTransform().getPosition());
                shaderOnUse.setVector3f(stringLightAmbient.c_str(), light->getAmbientColor());
                shaderOnUse.setVector3f(stringLightNoDiffuse.c_str(), light->getDiffuseColor());
                shaderOnUse.setVector3f(stringLightNoSpecular.c_str(), light->getSpecular());
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



