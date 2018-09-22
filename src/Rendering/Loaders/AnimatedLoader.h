//
// Created by erick on 9/19/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_ANIMATEDLOADER_H
#define MORDEROPENGLUDEMYTUTORIAL_ANIMATEDLOADER_H

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
#include "../../Animation/AnimatedEntity.h"

class AnimatedLoader {
public:

    AnimatedLoader();

    bool LoadAnimatedObject(std::string path, AnimatedEntity* root, bool * options);
//
//    bool LoadGameObject(std::string path, std::map<TextureTypeEnum, std::string> textureLocations, MeshedEntity *root, bool *options);
//
//    bool LoadGameObject(std::string path, std::map<TextureTypeEnum, std::string*> textureAtlases, MeshedEntity *root, bool *options);

    void processNode(aiNode *node, const aiScene *scene, AnimatedEntity* root);

    AnimatedEntity* processObject(aiMesh *mesh, const aiScene *scene);

    std::vector<Texture*> loadMaterialTextures(aiMaterial *material, aiTextureType type, TextureTypeEnum typeName);

    void Clean();

private:
    std::string directory;
    std::string path;
    std::vector<Texture*> textures_loaded;
//    mutable bool options[Num_Options];
    bool hasTransparency = false;
    bool withTexManuallyProvided = false;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_ANIMATEDLOADER_H
