#pragma once

#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <soil.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Material.h"

class ModelComponent {
public:
	ModelComponent() = default;

	ModelComponent(Mesh &mesh, Transform &transform, Material &material) :
		m_mesh(mesh), m_transform(transform), m_material(material) {}

	Mesh& getMesh() { return m_mesh; }

	void setMesh(Mesh& m_mesh) { ModelComponent::m_mesh = m_mesh; }

	Transform& getTransform() { return m_transform; }

	void setTransform(Transform& m_transform) { ModelComponent::m_transform = m_transform; }

	Material& getMaterial() { return m_material; }

	void setMaterial(Material& m_material) { ModelComponent::m_material = m_material; }

private:
	Mesh m_mesh;

	Material m_material;

	Transform m_transform;
};


class Model
{
public:

	Model();

	Model(const char* path);

	~Model();

	void Draw(Shader* shader, bool shadowPass);

private:
	std::vector<ModelComponent> components;

	std::string directory;
	
	std::vector<Texture> textures_loaded;

	bool isScaled;

	void loadModel(std::string path);

	void processNode(aiNode *node, const aiScene *scene);

	void processComponent(aiMesh *mesh, const aiScene *scene);

	std::vector<Texture> loadMaterialTextures(aiMaterial *material, aiTextureType type, TextureTypeEnum typeName);
};

