#include "EngineRendererGL.h"
#include "EngineCamera.h"
#include "RenderComponent.h"

void EngineRendererGL::loadMesh(Mesh *mesh){
    GLuint EBO, VBO;
    // Generate the VAO and VBO with only 1 object each
    glGenVertexArrays(1, &mesh->getId());
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

void EngineRendererGL::drawAll(const Scene &scene) {
    for(auto & object : scene.objects){
        for(auto & component : object->getRenderComponents()){
            component->getMaterial().getShader().use();
            component->getMaterial().getShader().setMatrix4("proj_matrix", scene.camera->getProjMatrix());
            component->getMaterial().getShader().setMatrix4("view_matrix", scene.camera->getViewMatrix());
            component->getMaterial().getShader().setMatrix4("transform", component->getOwner()->transform.getMoveMatrix());
            if(component->getMesh() != nullptr)
                drawMesh(component->getMesh());
        }
    }
}

void EngineRendererGL::drawMesh(Mesh *mesh) {
    auto it = find(loadedMeshIds.begin(), loadedMeshIds.end(), &mesh->getId());
    if(it == loadedMeshIds.end()){
        loadedMeshIds.emplace_back(&mesh->getId());
        loadMesh(mesh);
    }
    glBindVertexArray(mesh->getId());
    glDrawElements(GL_TRIANGLES , mesh->getIndices().size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void EngineRendererGL::cleanRenderer() {
    for(auto & vao : loadedMeshIds){
        glDeleteVertexArrays(1, vao);
    }
}


