#ifndef SKYBOX_H
#define SKYBOX_H

#include <vector>
#include <map>
#include <string>
#include "GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shaders/Shader.h"
#include "Mesh.h"
#include "../Core/Components/EntityComponent.h"

class RenderingEngine;
class Fog;

class SkyBox {
public:
	SkyBox();
	SkyBox(float size,std::map<SkyBoxTypes, std::vector<std::string>> faceLocations);
	
//	void Draw(Camera camera, const glm::mat4& projectionMatrix);

	Mesh *getSkyMesh() const;

	GLuint* getTextures();

    Transform& getTransform();

    ~SkyBox();

    SkyBox* AddComponent(EntityComponent<SkyBox,RenderingEngine>* component);

    void Update(float delta);

	void Render(RenderingEngine *engine);

	Fog *getFog();

	float getFogLowerLimit();

	float getFogUpperLimit();

	void setFog(Fog *fog);

	void setFogLowerLimit(float fog_lower_limit);

    void setFogUpperLimit(float fog_upper_limit);

    float getRotationSpeed();

    void setRotationSpeed(float rotationSpeed);

    void setBlendFactor(float blend_factor);

    float getBlendFactor() const;

private:

    std::map<SkyBoxTypes, std::vector<std::string>> m_faceLocations;

	std::vector<EntityComponent<SkyBox,RenderingEngine>*> m_components;

	float SIZE = 500.0f;
	Mesh * m_skyMesh;
	GLuint m_textures[NUM_SKYBOX_TYPES];
    Transform m_transform;
    float blend_factor = 0;
    float rotationSpeed = 0.1f;

	Fog* m_fog = nullptr;
	float fog_lower_limit = 0.0;
	float fog_upper_limit = 0.0;

    void SetupMesh();

	void LoadTextures();

};

#endif
