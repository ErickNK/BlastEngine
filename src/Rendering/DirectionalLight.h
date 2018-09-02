//
// Created by erick on 8/24/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_DIRECTIONALLIGHT_H
#define MORDEROPENGLUDEMYTUTORIAL_DIRECTIONALLIGHT_H

#include "Light.h"
#include "../Core/CommonValues.h"

class DirectionalLight : public Light {

public:
    DirectionalLight();

    DirectionalLight(glm::vec3 color,glm::vec3 direction,GLfloat ambientIntensity, GLfloat diffuseIntensity,
		GLfloat shadowWidth, GLfloat shadowHeight);

    ~DirectionalLight() override;

	void SetupLightSpace(DirectionalLightUniforms *directionalLightUniforms, GLuint shaderProgram);

	void UseLight(DirectionalLightUniforms *directionalLightUniforms,int shadowTextureUnit);
	
    static void SetupUniforms(DirectionalLightUniforms *directionalLightUniforms,GLuint shaderProgram);

private:

    glm::vec3 direction;

};


#endif //MORDEROPENGLUDEMYTUTORIAL_DIRECTIONALLIGHT_H
