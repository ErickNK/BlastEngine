#include <utility>

//
// Created by erick on 9/9/18.
//

#include "MeshedLoader.h"
#include "../../Core/Entities/MeshedEntity.h"
#include "../../Core/Components/RenderingComponents/MeshedRendererComponent.h"
#include "../TextureAtlas.h"


MeshedLoader::MeshedLoader() = default;

void MeshedLoader::Clean(){
    withTexManuallyProvided = false;

    this->textures_loaded.clear();

    hasTransparency = false;

    for (bool &option : options) {
        option = false;
    }
}

bool MeshedLoader::LoadGameObject(std::string path,
        std::map<TextureTypeEnum, std::string> textureLocations,
        MeshedEntity *root, bool *options) {
    withTexManuallyProvided = true;
    std::copy(options, options + Num_Options, MeshedLoader::options);

    for (auto const& x : textureLocations) {
        this->textures_loaded.push_back( new Texture(x.second, x.first)); //Keep so we don't reload it.
    }

    return LoadGameObject(std::move(path),root,MeshedLoader::options);
}

bool MeshedLoader::LoadGameObject(std::string path,
        std::map<TextureTypeEnum, std::string*> textureAtlases,
        MeshedEntity *root, bool *options) {
    withTexManuallyProvided = true;
    std::copy(options, options + Num_Options, MeshedLoader::options);

    for (auto const& x : textureAtlases) {
        int index = stoi(std::string(x.second[1]));
        int numberOfRows = stoi(std::string(x.second[2]));
        this->textures_loaded.push_back( new TextureAtlas(x.second[0], x.first,index,numberOfRows)); //Keep so we don't reload it.
    }

    return LoadGameObject(std::move(path),root,MeshedLoader::options);
}


bool MeshedLoader::LoadGameObject(std::string path, MeshedEntity* root, bool* options) {
    MeshedLoader::path = path;
    MeshedLoader::directory = path.substr(0, path.find_last_of('/'));
    std::copy(options, options + Num_Options, MeshedLoader::options);

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return false;
    }

    this->processNode(scene->mRootNode, scene, root);

    Clean();

    return true;
}

void MeshedLoader::processNode(aiNode * node, const aiScene * scene, MeshedEntity* root) {

    //Process leaf nodes
    for (GLuint i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];

        //Process Object
        MeshedEntity * child = this->processObject(mesh, scene);

        //Add Components
        child->AddComponent(new MeshedRendererComponent());

        //Add children
        root->AddChild(child);
    }

    //Process nodes
    for (GLuint i = 0; i < node->mNumChildren; i++) {
        auto * group = new MeshedEntity();

        this->processNode(node->mChildren[i], scene, group);

        //Add node
        root->AddChild(group);
    }
}

MeshedEntity* MeshedLoader::processObject(aiMesh *mesh, const aiScene *scene) {

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture*> textures;
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
        Vertex vertex;
        glm::vec3 vector;

        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.SetPos(vector);

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


        if (mesh->mTextureCoords[0]) {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.SetTexCoord(vec);
        }
        else {
            vertex.SetTexCoord(glm::vec2(0.0f, 0.0f));
        }

        vertex.SetColor(color);
        vertices.push_back(vertex);
    }

    //TODO : a way to set the specular intensity and shininess of object
    return new MeshedEntity(
            *new Mesh(vertices, vertices.size(), indices, indices.size()),
            *new Transform(),
            *new Material(0.3f, 12.0f, textures, options)
    );
}

std::vector<Texture*> MeshedLoader::loadMaterialTextures(aiMaterial * material, aiTextureType type, TextureTypeEnum typeName) {
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