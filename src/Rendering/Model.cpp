#include "Model.h"

Model::Model() = default;

Model::Model(const char* path)
{
	loadModel(std::string(path));
}

Model::~Model() {}

void Model::Draw(Shader* shader, bool shadowPass){
	for (GLuint i = 0; i < this->components.size(); i++) {

		shader->UpdateModel(this->components[i].getTransform());
		
		if (!shadowPass) {

			if (this->components[i].getTransform().isNonUnformScaled()) {
				shader->UpdateNormalMatrix(
					glm::mat3(glm::transpose(glm::inverse(this->components[i].getTransform().GetModel())))
				);
			} else {
				shader->UpdateNormalMatrix(
					glm::mat3(components[i].getTransform().GetModel())
				);
			}

			this->components[i].getMaterial().UseMaterial(shader);
		}

		this->components[i].getMesh().Draw();

		if (!shadowPass) {
			shader->resetDrawingTextureUnits();
		}
	}
}

void Model::loadModel(std::string path) {
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}

	this->directory = path.substr(0, path.find_last_of('/'));

	this->processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode * node, const aiScene * scene) {

	for (GLuint i = 0; i < node->mNumMeshes; i++) {
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		this->processComponent(mesh, scene);
	}

	for (GLuint i = 0; i < node->mNumChildren; i++) {
		this->processNode(node->mChildren[i], scene);
	}
}

void Model::processComponent(aiMesh * mesh, const aiScene * scene) {

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;
	
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
		vertices.push_back(vertex);
	}

	//Process the indices
	for (GLuint i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];

		for (GLuint j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	//Process the textures
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

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

	components.emplace_back(
		 Mesh(vertices, vertices.size(), indices, indices.size()),
		 Transform(),
		 Material(1.0f, 1.0f, textures)
	);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial * material, aiTextureType type, TextureTypeEnum typeName) {
	std::vector<Texture> textures;

	for (GLuint i = 0; i < material->GetTextureCount(type); i++) {

		aiString str;

		material->GetTexture(type, i, &str);

		GLboolean skip = false;

		//Search for already loaded textures.
		for (GLuint j = 0; j < textures_loaded.size(); j++) {
			if (textures_loaded[j].GetFileLocation() == std::string(str.C_Str())) { //if already loaded
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}

		//TODO: configure Texture class
		if (!skip) { //If not loaded
			Texture texture = *new Texture(std::string(str.C_Str()), this->directory, typeName);
			textures.push_back(texture);

			this->textures_loaded.push_back(texture); //Keep so we don't reload it.
		}
	}

	return textures;
}
