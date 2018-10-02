//
// Created by erick on 9/30/18.
//

#include "AnimationLoader.h"
AnimationLoader::AnimationLoader() = default;

void AnimationLoader::Clean(){
    m_key_frames.clear();
    m_joint_transforms.clear();
}

std::vector<Animation*> AnimationLoader::LoadAnimations(std::string path){
    std::vector<Animation*> animations;
    AnimationLoader::path = path;
    AnimationLoader::directory = path.substr(0, path.find_last_of('/'));

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_LimitBoneWeights );

    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return animations;
    }

    for(GLuint i = 0; i < scene->mNumAnimations; i++){

        animations.push_back(this->processAnimation(scene->mAnimations[i], scene));

    }

    return animations;
}

Animation* AnimationLoader::processAnimation(aiAnimation *animation, const aiScene * scene) {
    auto *anim = new Animation;

    anim->setName(animation->mName.C_Str());

    animation->mTicksPerSecond = animation->mTicksPerSecond != 0 ? animation->mTicksPerSecond : 25.0f;

    anim->setLength(animation->mDuration / animation->mTicksPerSecond);

    for (GLuint i = 0; i < animation->mNumChannels; i++) {
        this->processNodeAnim(animation->mChannels[i], animation);
    }

    for (auto const& x : m_key_frames) {
        anim->addKeyFrames(x.second);
    }

    Clean();

    return anim;
}

void AnimationLoader::processNodeAnim(aiNodeAnim *nodeAnim, aiAnimation *animation) {

    for (GLuint i = 0; i < nodeAnim->mNumPositionKeys; i++) { //Go through all keyframes of node
        auto * jointTransform = new JointTransform();
        glm::vec3 vector;
        glm::quat quat;

        //POSITION for key frame
        vector.x = nodeAnim->mPositionKeys[i].mValue.x;
        vector.y = nodeAnim->mPositionKeys[i].mValue.x;
        vector.z = nodeAnim->mPositionKeys[i].mValue.x;

        jointTransform->setPosition(vector);

        //ROTATION for key frame
        quat.x = nodeAnim->mRotationKeys[i].mValue.x;
        quat.y = nodeAnim->mRotationKeys[i].mValue.x;
        quat.z = nodeAnim->mRotationKeys[i].mValue.x;
        quat.w = nodeAnim->mRotationKeys[i].mValue.w;

        jointTransform->setRot(quat);

        //SCALE for key frame
        vector.x = nodeAnim->mScalingKeys[i].mValue.x;
        vector.y = nodeAnim->mScalingKeys[i].mValue.x;
        vector.z = nodeAnim->mScalingKeys[i].mValue.x;

        jointTransform->setScale(vector);

        double timestamp = nodeAnim->mPositionKeys[i].mTime/animation->mTicksPerSecond;

        if(m_key_frames.find(timestamp) == m_key_frames.end()) { //If keyframe not already collected
            auto *keyFrame = new KeyFrame();

            keyFrame->setTimestamp(timestamp); //timestamp
            keyFrame->addJointTransform(nodeAnim->mNodeName.C_Str(), jointTransform);

            m_key_frames[timestamp] = keyFrame;
        }else{ //This may be a new node
            m_key_frames[timestamp]->addJointTransform(nodeAnim->mNodeName.C_Str(),jointTransform);
        }
    }

    if(nodeAnim->mPreState == aiAnimBehaviour_DEFAULT){ //No animation, add identity pose
        auto * jointTransform = new JointTransform();

        jointTransform->setPosition(glm::vec3(0));
        jointTransform->setRot(glm::quat());
        jointTransform->setScale(glm::vec3(1));

        if(m_key_frames.find(0) == m_key_frames.end()) { //If keyframe not already collected
            auto *keyFrame = new KeyFrame();

            keyFrame->setTimestamp(0); //timestamp
            keyFrame->addJointTransform(nodeAnim->mNodeName.C_Str(), jointTransform);

            m_key_frames[0] = keyFrame;
        }else{ //This may be a new node
            m_key_frames[0]->addJointTransform(nodeAnim->mNodeName.C_Str(),jointTransform);
        }

    }

}
