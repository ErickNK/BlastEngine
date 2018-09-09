#ifndef SKYBOX_H
#define SKYBOX_H

#include <vector>
#include <string>
#include "GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shaders/Shader.h"
#include "Mesh.h"

class SkyBox {
public:
	SkyBox();
	SkyBox(std::vector<std::string> faceLocations);

	
	void Draw(Camera camera, const glm::mat4& projectionMatrix);

	~SkyBox();

private:
	std::vector<std::string> m_faceLocations;

	Mesh * m_skyMesh;
	Shader * m_skyShader;

	GLuint m_texture;

	void SetupMesh();
	void LoadTextures();
};

#endif
