//
// Created by erick on 9/19/18.
//

#include "AnimatedLoader.h"
#include "../../Core/Components/RenderingComponents/MeshedRendererComponent.h"
#include "../../Animation/AnimatedEntity.h"
#include "../../Core/Components/RenderingComponents/AnimatedRendererComponent.h"
#include "../../Common/Util.h"
#include "MeshedLoader.h"
#include "../../Animation/AnimationComponent.h"
#include "../TextureAtlas.h"

AnimatedLoader::AnimatedLoader() = default;

void AnimatedLoader::Clean(){
    withTexManuallyProvided = false;

    textures_loaded.clear();

    all_joints.clear();

    necessityMap.clear();

    for (bool &option : options) {
        option = false;
    }
}

bool AnimatedLoader::LoadAnimatedObject(std::string path,
                                  std::map<TextureTypeEnum, std::string> textureLocations,
                                  AnimatedEntity *root, bool *options) {
    withTexManuallyProvided = true;
    std::copy(options, options + Num_Options, AnimatedLoader::options);

    for (auto const& x : textureLocations) {
        this->textures_loaded.push_back( new Texture(x.second, x.first)); //Keep so we don't reload it.
    }

    return LoadAnimatedObject(std::move(path),root,AnimatedLoader::options);
}

bool AnimatedLoader::LoadAnimatedObject(std::string path,
                                  std::map<TextureTypeEnum, std::string*> textureAtlases,
                                  AnimatedEntity *root, bool *options) {
    withTexManuallyProvided = true;
    std::copy(options, options + Num_Options, AnimatedLoader::options);

    for (auto const& x : textureAtlases) {
        int index = stoi(std::string(x.second[1]));
        int numberOfRows = stoi(std::string(x.second[2]));
        this->textures_loaded.push_back( new TextureAtlas(x.second[0], x.first,index,numberOfRows)); //Keep so we don't reload it.
    }

    return LoadAnimatedObject(std::move(path),root,AnimatedLoader::options);
}



bool AnimatedLoader::LoadAnimatedObject(std::string path, AnimatedEntity *root, bool *options) {
    AnimatedLoader::path = path;
    AnimatedLoader::directory = path.substr(0, path.find_last_of('/'));
    std::copy(options, options + Num_Options, AnimatedLoader::options);

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path,
            aiProcess_Triangulate |
            aiProcess_FlipUVs   |
            aiProcess_CalcTangentSpace |
            aiProcess_LimitBoneWeights |
            aiProcess_GenSmoothNormals
            );

    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return false;
    }

    this->processNode(scene->mRootNode, scene, root, aiMatrix4x4());

    Joint * rootJoint = nullptr;
    this->processSkeleton(scene->mRootNode, rootJoint, root);

    root->AddComponent(new AnimationComponent());

    Clean();

    return true;
}

void AnimatedLoader::processNode(aiNode * node, const aiScene * scene, AnimatedEntity* root, aiMatrix4x4 accTransform) {

    node->mTransformation = node->mTransformation * accTransform;

    //Process leaf nodes
    for (GLuint i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];

        //Process Object
        AnimatedEntity * child = this->processObject(node, mesh, scene);

        //Add Components
        this->AddComponents(child);

        //Add children
        root->AddChild(child);
    }

    //Process nodes
    for (GLuint i = 0; i < node->mNumChildren; i++) {
        auto * group = new AnimatedEntity();

        this->processNode(node->mChildren[i], scene, group, node->mTransformation);

        //Add node
        root->AddChild(group);
    }
}

AnimatedEntity* AnimatedLoader::processObject(aiNode * node, aiMesh *mesh, const aiScene *scene) {

    std::vector<AnimatedVertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture*> textures;
    std::vector<Joint*> joints;
    glm::vec4 color = glm::vec4(1,1,1,1);


    //Process the indices
    for (GLuint i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];

        for (GLuint j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    //Process the textures and colors
    if (mesh->mMaterialIndex >= 0 && !withTexManuallyProvided) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];


        aiColor4D diffuseColor;
        if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuseColor)) {
            color = glm::vec4(diffuseColor.r, diffuseColor.g, diffuseColor.b, diffuseColor.a);
        }
//
//        aiColor4D ambientColor;
//        if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambientColor)) {
//            color = glm::vec4(ambientColor.r, ambientColor.g, ambientColor.b, ambientColor.a);
//            colors.push_back(color);
//        }

        std::vector<Texture*> diffuseMaps = this->loadMaterialTextures(
                material,
                aiTextureType_DIFFUSE,
                DIFFUSE_TEXTURE
        );
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<Texture*> specularMaps = this->loadMaterialTextures(
                material,
                aiTextureType_SPECULAR,
                SPECULAR_TEXTURE
        );
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }else{
        if (withTexManuallyProvided){
            textures = textures_loaded;
        }
    }

    //Process the vertices
    for (GLuint i = 0; i < mesh->mNumVertices; i++) {
        AnimatedVertex vertex;
        glm::vec3 vector;

        //POSITION
        {
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.SetPos(vector);
        }

        //NORMALS
        if (mesh->mNormals != NULL) {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.SetNormal(vector);
        }
        else {
            vector.x = 0;
            vector.y = 0;
            vector.z = 0;
            vertex.SetNormal(vector);
        }

        //TEXTURE COORDS
        if (mesh->mTextureCoords[0]) {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.SetTexCoord(vec);
        }
        else {
            vertex.SetTexCoord(glm::vec2(0.0f, 0.0f));
        }

        //TANGENTS
        if (mesh->HasTangentsAndBitangents()) {
            glm::vec3 vec;
            vec.x = mesh->mTangents[i].x;
            vec.y = mesh->mTangents[i].y;
            vec.z = mesh->mTangents[i].z;
            vertex.SetTangent(vec);
        }
        else {
            vertex.SetTangent(glm::vec3(0.0f, 1.0f, 0.0f));
        }

        vertex.SetColor(color);
        vertices.push_back(vertex);
    }

    // BONES
    for(unsigned int b = 0; b < mesh->mNumBones; b++){
        if(joints.size() <= MAX_JOINTS_PER_MESH){

            aiBone* bone = mesh->mBones[b];

            auto * joint = new Joint();

            joint->setMeshIndex(b);
            joint->setName(bone->mName.C_Str());

            glm::mat4 offsetMatrix = Util::fromAssimp(bone->mOffsetMatrix);
            joint->setLocalOriginalTransform(offsetMatrix);

            //Find the nodes necessary for skeleton
            processBone(scene->mRootNode,node,bone);

            //Weights and affected vertices
            for(int w = 0; w < bone->mNumWeights; w++) {

                aiVertexWeight weight = bone->mWeights[w];

                int vertexIndex = weight.mVertexId;

                if(vertices[vertexIndex].getWeightCount() <= MAX_JOINTS_PER_VERTEX){

                    vertices[vertexIndex].setJointID(vertices[vertexIndex].getWeightCount(), b);

                    vertices[vertexIndex].setJointWeight(vertices[vertexIndex].getWeightCount(), weight.mWeight);

                    vertices[vertexIndex].getWeightCount()++;

                }else{
                    std::cerr << "Only " << MAX_JOINTS_PER_VERTEX << " are allowed per vertex" << std::endl;
                }
            }

            joints.push_back(joint);
            all_joints[bone->mName.C_Str()] = joint;
        }
    }

    return new AnimatedEntity(
            *new AnimatedMesh(vertices, vertices.size(), indices, indices.size()),
            *new Transform(),
            *new Material(7.0f, 30.0f, textures, options),
            joints
    );
}

void AnimatedLoader::processBone(aiNode *node, aiNode *meshNode, aiBone *bone) {
    if(node->mName == bone->mName){
        AddNecessityRecursively(node,meshNode);
        return;
    }else{
        for (GLuint i = 0; i < node->mNumChildren; i++) {
            this->processBone(node->mChildren[i], meshNode, bone);
        }
    }
}

void AnimatedLoader::processSkeleton(aiNode *node, Joint* rootJoint, AnimatedEntity* root) {
    //if not necessarry skip
    if(necessityMap.find(node->mName.C_Str()) == necessityMap.end()) return;


    //Is in skeleton
    if(rootJoint == nullptr){
        if(all_joints[node->mName.C_Str()] != nullptr) {
            root->setRootJoint(all_joints[node->mName.C_Str()]);
        }
    }else{
        if(all_joints[node->mName.C_Str()] != nullptr) {
            rootJoint->addChild(all_joints[node->mName.C_Str()]);
        }
    }

    //Process child joints
    for (GLuint i = 0; i < node->mNumChildren; i++) {

        processSkeleton(node->mChildren[i],all_joints[node->mName.C_Str()],root);

    }
}

void AnimatedLoader::AddNecessityRecursively(aiNode *node, aiNode *meshNode){
    //If not already in map add it.
    if(necessityMap.find(node->mName.C_Str()) == necessityMap.end()){
        necessityMap[node->mName.C_Str()] = (node);
    }

    if(node->mName == meshNode->mName) return;

    if(node->mName == meshNode->mParent->mName) return;

//    if(node->mParent == nullptr) return;

    AddNecessityRecursively(node->mParent,meshNode);
}

std::vector<Texture*> AnimatedLoader::loadMaterialTextures(aiMaterial * material, aiTextureType type, TextureTypeEnum typeName) {
    std::vector<Texture*> textures;

    for (GLuint i = 0; i < material->GetTextureCount(type); i++) {

        aiString str;

        material->GetTexture(type, i, &str);

        GLboolean skip = false;

        //Search for already loaded textures.
        for (GLuint j = 0; j < this->textures_loaded.size(); j++) {
            if (this->textures_loaded[j]->GetFileLocation() == std::string(str.C_Str())) { //if already loaded
                textures.push_back(this->textures_loaded[j]);
                skip = true;
                break;
            }
        }

        //TODO: configure Texture class
        if (!skip) { //If not loaded
            Texture* texture = new Texture(std::string(str.C_Str()), directory, typeName);
            textures.push_back(texture);

            this->textures_loaded.push_back(texture); //Keep so we don't reload it.
        }
    }

    return textures;
}

void AnimatedLoader::AddComponents(AnimatedEntity *entity) {
    entity->AddComponent(new AnimatedRendererComponent());
//    entity->AddComponent(new AnimationComponent());
}
