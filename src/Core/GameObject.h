//
// Created by erick on 9/7/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_GAMEOBJECT_H
#define MORDEROPENGLUDEMYTUTORIAL_GAMEOBJECT_H

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
#include "Input.h"
#include "../Rendering/Shaders/Shader.h"
#include "../Rendering/Camera.h"
#include "../Rendering/Mesh.h"
#include "../Rendering/Material.h"

class CoreEngine;

class GameComponent;

class GameObject {

public:
    GameObject() = default;

    explicit GameObject(std::string path);

    GameObject(Mesh &mesh, Transform &transform, Material &material) :
            m_mesh(mesh), m_transform(transform), m_material(material) {}

    virtual ~GameObject();

    void ProcessInputAll(const Input* input, float delta);

    void UpdateAll(float delta);

    void RenderAll(Shader* shader) const;

    GameObject* AddChild(GameObject* child);

    GameObject* AddComponent(GameComponent* component);

    std::vector<GameObject*> GetAllAttached();

    Mesh& getMesh() { return m_mesh; }

    void setMesh(Mesh& m_mesh) { GameObject::m_mesh = m_mesh; }

    Transform& getTransform() { return m_transform; }

    void setTransform(Transform& m_transform) { GameObject::m_transform = m_transform; }

    Material& getMaterial() { return m_material; }

    void setMaterial(Material& m_material) { GameObject::m_material = m_material; }

    bool getIsLoadedCorrectly() const;

    bool LoadGameObject();

    void processNode(aiNode *node, const aiScene *scene);

    void SetEngine(CoreEngine* engine);

protected:
    std::vector<GameObject*> m_children;
    std::vector<GameComponent*> m_components;
    CoreEngine* m_coreEngine = nullptr;

    std::string directory;
    std::string path;
    std::vector<Texture> textures_loaded;
    bool isLoadedCorrectly = false;

    Mesh m_mesh;
    Material m_material;
    Transform m_transform;

    void ProcessInput(const Input* input, float delta);

    void Update(float delta);

    void Render(Shader* shader) const;

    GameObject* processObject(aiMesh *mesh, const aiScene *scene);

    std::vector<Texture> loadMaterialTextures(aiMaterial *material, aiTextureType type, TextureTypeEnum typeName);
};


#endif //MORDEROPENGLUDEMYTUTORIAL_GAMEOBJECT_H
