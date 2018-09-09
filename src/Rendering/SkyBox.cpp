#include "SkyBox.h"
#include <cassert>
#include <iostream>
#include <fstream>

SkyBox::SkyBox(){}

SkyBox::SkyBox(std::vector<std::string> faceLocations):
	m_faceLocations(faceLocations)
{
	std::map<int, std::string> shaderFiles;

	shaderFiles[GL_VERTEX_SHADER] = "../res/shaders/SkyBox.vert";
	shaderFiles[GL_FRAGMENT_SHADER] = "../res/shaders/SkyBox.frag";
	m_skyShader = new Shader(shaderFiles,SKY_BOX_SHADER);
	m_skyShader->Init();

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
		Vertex(glm::vec3(-1.0f, 1.0f, -1.0f)),
		Vertex(glm::vec3(-1.0f, -1.0f, -1.0f)),
		Vertex(glm::vec3(1.0f, 1.0f, -1.0f)),
		Vertex(glm::vec3(1.0f, -1.0f, -1.0f)),

		Vertex(glm::vec3(-1.0f, 1.0f, 1.0f)),
		Vertex(glm::vec3(1.0f, 1.0f, 1.0f)),
		Vertex(glm::vec3(-1.0f, -1.0f, 1.0f)),
		Vertex(glm::vec3(1.0f, -1.0f, 1.0f))
	};

	m_skyMesh = new Mesh(skyboxVertices, sizeof(skyboxVertices) / sizeof(skyboxVertices[0]), skyboxIndices, sizeof(skyboxIndices) / sizeof(skyboxIndices[0]));
}

void SkyBox::LoadTextures() {

	glGenTextures(1, &m_texture); 
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);

		int width, height, bitDepth;

		for (size_t i = 0; i < 6; i++) {

			unsigned char* texture_data = stbi_load(m_faceLocations[i].c_str(), &width, &height, &bitDepth, 0);

			if (texture_data == nullptr) {
				std::cerr << "Error: Texture loading failed for:" << m_faceLocations[i] << std::endl;
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

}

void SkyBox::Draw(Camera camera,const glm::mat4& projectionMatrix)
{

	camera.setViewMatrix(glm::mat4(glm::mat3(camera.getViewMatrix())));

	glDepthMask(GL_FALSE);
		m_skyShader->Bind();
			
			m_skyShader->UpdateView(camera);

			m_skyShader->UpdateProjection(projectionMatrix);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);

			m_skyMesh->Draw();

		m_skyShader->UnBind();
	glDepthMask(GL_TRUE);

}

SkyBox::~SkyBox(){}
