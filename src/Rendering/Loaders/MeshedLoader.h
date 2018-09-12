//
// Created by erick on 9/9/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_MODELLOADER_H
#define MORDEROPENGLUDEMYTUTORIAL_MODELLOADER_H

#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../Texture.h"
#include "../../Core/Entities/MeshedEntity.h"

class MeshedLoader {
public:

    MeshedLoader();

    bool LoadGameObject(std::string path, MeshedEntity* root);

    bool LoadGameObjectWithTexture(std::string path,std::map<TextureTypeEnum, std::string> textureLocations, MeshedEntity *root);

    void processNode(aiNode *node, const aiScene *scene, MeshedEntity* root);

    MeshedEntity* processObject(aiMesh *mesh, const aiScene *scene);

    std::vector<Texture> loadMaterialTextures(aiMaterial *material, aiTextureType type, TextureTypeEnum typeName);
private:
    std::string directory;
    std::string path;
    std::vector<Texture> textures_loaded;
    bool isLoadedCorrectly = false;

};


#endif //MORDEROPENGLUDEMYTUTORIAL_MODELLOADER_H
