#include <utility>

#include "SkyBox.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include "RenderingEngine.h"

SkyBox::SkyBox(){}

SkyBox::SkyBox(float size,std::map<SkyBoxTypes, std::vector<std::string>> faceLocations):
    SIZE(size),
	m_faceLocations(std::move(faceLocations))
{
	LoadTextures();
	SetupMesh();
}

void SkyBox::SetupMesh() {
	unsigned int skyboxIndices[] = {
		// front
		0, 1, 2,
		2, 1, 3,
		// right
		2, 3, 5,
		5, 3, 7,
		// back
		5, 7, 4,
		4, 7, 6,
		// left
		4, 6, 0,
		0, 6, 1,
		// top
		4, 0, 5,
		5, 0, 2,
		// bottom
		1, 6, 3,
		3, 6, 7
	};

	Vertex skyboxVertices[] = {
		Vertex(glm::vec3(-SIZE, SIZE, -SIZE)),
		Vertex(glm::vec3(-SIZE, -SIZE, -SIZE)),
		Vertex(glm::vec3(SIZE, SIZE, -SIZE)),
		Vertex(glm::vec3(SIZE, -SIZE, -SIZE)),

		Vertex(glm::vec3(-SIZE, SIZE, SIZE)),
		Vertex(glm::vec3(SIZE, SIZE, SIZE)),
		Vertex(glm::vec3(-SIZE, -SIZE, SIZE)),
		Vertex(glm::vec3(SIZE, -SIZE, SIZE))
	};

	m_skyMesh = new Mesh(skyboxVertices, sizeof(skyboxVertices) / sizeof(skyboxVertices[0]), skyboxIndices, sizeof(skyboxIndices) / sizeof(skyboxIndices[0]));
}

void SkyBox::LoadTextures() {

    int count = 0;
	for(auto &x : m_faceLocations) {
		glGenTextures(1, &m_textures[count]);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_textures[count]);

		int width, height, bitDepth;

		for (size_t i = 0; i < 6; i++) {

			unsigned char *texture_data = stbi_load(x.second[i].c_str(), &width, &height, &bitDepth, 0);

			if (texture_data == nullptr) {
				std::cerr << "Error: Texture loading failed for:" << x.second[i] << std::endl;
				return;
			}

			GLenum format;
			if (bitDepth == 1)
				format = GL_RED;
			else if (bitDepth == 3)
				format = GL_RGB;
			else if (bitDepth == 4)
				format = GL_RGBA;


			glTexImage2D(
					GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, //Texture target
					0, // Mipmap Level
					format, // Format of how it will be stored
					width, height, // Width and height of the image/data being loaded
					0, // Should always be 0, Legacy option that defines whether to add borders to the texture.
					format, // Format of the data being loaded
					GL_UNSIGNED_BYTE, // Data type of the values
					texture_data // Data itself
			);

			stbi_image_free(texture_data);
		}

		//WRAP filter
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		//Overlap filter
		glTexParameterf(
				GL_TEXTURE_CUBE_MAP,
				GL_TEXTURE_MIN_FILTER, // Applied when texture is further away/smaller
				GL_LINEAR
		);
		glTexParameterf(
				GL_TEXTURE_CUBE_MAP,
				GL_TEXTURE_MAG_FILTER, // Applied when texture is closer/bigger
				GL_LINEAR
		);

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		count++;
	}

}

SkyBox::~SkyBox(){}

Mesh *SkyBox::getSkyMesh() const {
    return m_skyMesh;
}

GLuint* SkyBox::getTextures() {
    return m_textures;
}

void SkyBox::Update(double time, float delta) {
	for (auto m_component : m_components) {
		m_component->Update(time,delta);
	}
}

void SkyBox::Render(RenderingEngine *engine) {
    for (auto m_component : m_components) {
        m_component->Render(engine);
    }
}

SkyBox* SkyBox::AddComponent(EntityComponent<SkyBox>* component) {
    m_components.push_back(component);
    component->SetParent(this);
    return this;
}

Fog *SkyBox::getFog() {
    return m_fog;
}

float SkyBox::getFogLowerLimit() {
    return fog_lower_limit;
}

float SkyBox::getFogUpperLimit() {
    return fog_upper_limit;
}

void SkyBox::setFog(Fog *fog) {
	m_fog = fog;
}

void SkyBox::setFogLowerLimit(float fog_lower_limit) {
	SkyBox::fog_lower_limit = fog_lower_limit;
}

void SkyBox::setFogUpperLimit(float fog_upper_limit) {
	SkyBox::fog_upper_limit = fog_upper_limit;
}

void SkyBox::setRotationSpeed(float rotationSpeed) {
	SkyBox::rotationSpeed = rotationSpeed;
}

float SkyBox::getRotationSpeed() {
	return rotationSpeed;
}

void SkyBox::setBlendFactor(float blend_factor) {
    SkyBox::blend_factor = blend_factor;
}

float SkyBox::getBlendFactor() const {
    return blend_factor;
}



