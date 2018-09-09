//
// Created by erick on 9/7/18.
//

#include "GameObject.h"
#include "Components/GameComponent.h"
#include "Components/MeshRenderer.h"

GameObject::GameObject(std::string path):
    path(path),
    directory(path.substr(0, path.find_last_of('/'))) {}

GameObject::~GameObject()
{
    for (auto &m_component : m_components) {
        delete m_component;
    }

    for (auto &i : m_children) {
        delete i;
    }
}

GameObject* GameObject::AddChild(GameObject* child)
{
    m_children.push_back(child);
//    child->GetTransform()->SetParent(&m_transform);
//    child->SetEngine(m_coreEngine);
    return this;
}

GameObject* GameObject::AddComponent(GameComponent* component)
{
    m_components.push_back(component);
    component->SetParent(this);
    return this;
}

void GameObject::ProcessInputAll(const Input* input, float delta)
{
    ProcessInput(input, delta);

    for (auto &i : m_children) {
        i->ProcessInputAll(input, delta);
    }
}

void GameObject::UpdateAll(float delta)
{
    Update(delta);

    for (auto &i : m_children) {
        i->UpdateAll(delta);
    }
}

void GameObject::RenderAll(Shader* shader) const
{
    Render(shader);

    for (auto i : m_children) {
        i->RenderAll(shader);
    }
}

void GameObject::ProcessInput(const Input* input, float delta)
{
//    m_transform.Update();

    for (auto &m_component : m_components) {
        m_component->ProcessInput(input, delta);
    }
}

void GameObject::Update(float delta)
{
    for (auto &m_component : m_components) {
        m_component->Update(delta);
    }
}

void GameObject::Render(Shader* shader) const
{
    for (auto m_component : m_components) {
        m_component->Render(shader);
    }
}

std::vector<GameObject*> GameObject::GetAllAttached()
{
    std::vector<GameObject*> result;

    for (auto &i : m_children) {
        std::vector<GameObject*> childObjects = i->GetAllAttached();
        result.insert(result.end(), childObjects.begin(), childObjects.end());
    }

    result.push_back(this);
    return result;
}

bool GameObject::LoadGameObject() {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return false;
    }

    this->processNode(scene->mRootNode, scene);

    return true;
}

void GameObject::processNode(aiNode * node, const aiScene * scene) {

    //Process leaf nodes
    for (GLuint i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];

        //Process Object
        GameObject * child = this->processObject(mesh, scene);

        //Add Components
        auto * renderer = new MeshRenderer(child);
        child->AddComponent(renderer);

        //Add children
        this->AddChild(child);
    }

    //Process nodes
    for (GLuint i = 0; i < node->mNumChildren; i++) {
        auto * group = new GameObject(path);

        group->processNode(node->mChildren[i], scene);

        //Add node
        this->AddChild(group);
    }
}

GameObject* GameObject::processObject(aiMesh *mesh, const aiScene *scene) {

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;
    glm::vec4 color = glm::vec4(1,1,1,1);

    //Process the indices
    for (GLuint i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];

        for (GLuint j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    //Process the textures and colors
    if (mesh->mMaterialIndex >= 0) {
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

        std::vector<Texture> diffuseMaps = this->loadMaterialTextures(
                material,
                aiTextureType_DIFFUSE,
                DIFFUSE_TEXTURE
        );
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<Texture> specularMaps = this->loadMaterialTextures(
                material,
                aiTextureType_SPECULAR,
                SPECULAR_TEXTURE
        );
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
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

    return new GameObject(
            *new Mesh(vertices, vertices.size(), indices, indices.size()),
            *new Transform(),
            *new Material(7.0f, 30.0f, textures)
    );
}

std::vector<Texture> GameObject::loadMaterialTextures(aiMaterial * material, aiTextureType type, TextureTypeEnum typeName) {
    std::vector<Texture> textures;

    for (GLuint i = 0; i < material->GetTextureCount(type); i++) {

        aiString str;

        material->GetTexture(type, i, &str);

        GLboolean skip = false;

        //Search for already loaded textures.
        for (GLuint j = 0; j < this->textures_loaded.size(); j++) {
            if (this->textures_loaded[j].GetFileLocation() == std::string(str.C_Str())) { //if already loaded
                textures.push_back(this->textures_loaded[j]);
                skip = true;
                break;
            }
        }

        //TODO: configure Texture class
        if (!skip) { //If not loaded
            Texture texture = *new Texture(std::string(str.C_Str()), directory, typeName);
            textures.push_back(texture);

            this->textures_loaded.push_back(texture); //Keep so we don't reload it.
        }
    }

    return textures;
}

void GameObject::SetEngine(CoreEngine* engine)
{
    if(m_coreEngine != engine)
    {
        m_coreEngine = engine;

        for(unsigned int i = 0; i < m_components.size(); i++)
        {
            m_components[i]->AddToEngine(engine);
        }

        for(unsigned int i = 0; i < m_children.size(); i++)
        {
            m_children[i]->SetEngine(engine);
        }
    }
}

bool GameObject::getIsLoadedCorrectly() const {
    return isLoadedCorrectly;
}
