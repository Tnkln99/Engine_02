#ifndef ENGINE_02_MODEL_H
#define ENGINE_02_MODEL_H
#include "Mesh.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class Model {
private:
    std::string nameOfModel;

    std::vector<Mesh> meshes;

    std::vector<Texture> textures_loaded;
    std::string directory;

    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                         std::string typeName);

    unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
public:
    Model(char *path)
    {
        loadModel(path);
    }

    std::string getNameOfModel();
    std::vector<Mesh> & getMeshes();
};


#endif //ENGINE_02_MODEL_H
