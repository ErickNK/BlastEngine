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
#include "MeshedLoader.h"

class AnimatedLoader {
public:

    AnimatedLoader();

    bool LoadAnimatedObject(std::string path, AnimatedEntity* root, bool * options);

    bool LoadAnimatedObject(std::string path, std::map<TextureTypeEnum, std::string> textureLocations, AnimatedEntity *root, bool *options);

    bool LoadAnimatedObject(std::string path, std::map<TextureTypeEnum, std::string*> textureAtlases, AnimatedEntity *root, bool *options);

    void processNode(aiNode *node, const aiScene *scene, AnimatedEntity* root, aiMatrix4x4 accTransform);

    void processSkeleton(aiNode *node, Joint* rootJoint, AnimatedEntity* root);

    void processBone(aiNode *node, aiNode *meshNode, aiBone *bone);

    AnimatedEntity* processObject(aiNode * node, aiMesh *mesh, const aiScene *scene);

    std::vector<Texture*> loadMaterialTextures(aiMaterial *material, aiTextureType type, TextureTypeEnum typeName);

    void AddNecessityRecursively(aiNode *node, aiNode *meshNode);

    void Clean();

private:
    std::string directory;
    std::string path;
    std::vector<Texture*> textures_loaded;

    std::map<std::string,Joint*> all_joints;
    std::map<std::string,aiNode*> necessityMap;

    mutable bool options[Num_Options];
    bool withTexManuallyProvided = false;

    void AddComponents(AnimatedEntity *entity);
};


#endif //MORDEROPENGLUDEMYTUTORIAL_ANIMATEDLOADER_H
