//
// Created by erick on 9/30/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_ANIMATIONLOADER_H
#define MORDEROPENGLUDEMYTUTORIAL_ANIMATIONLOADER_H

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
#include "../../Animation/Animation.h"
#include "../../Animation/Joint.h"

class AnimationLoader {
public:

    AnimationLoader();

    std::vector<Animation*> LoadAnimations(std::string path);

    Animation* processAnimation(aiAnimation *animation, const aiScene *scene);

    void Clean();

private:
    std::string directory;
    std::string path;

    std::map<double,std::string,JointTransform*> m_joint_transforms;
    std::map<double,KeyFrame*> m_key_frames;

    void processNodeAnim(aiNodeAnim *nodeAnim,aiAnimation *animation);
};


#endif //MORDEROPENGLUDEMYTUTORIAL_ANIMATIONLOADER_H
