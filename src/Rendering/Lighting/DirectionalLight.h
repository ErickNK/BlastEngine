//
// Created by erick on 8/24/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_DIRECTIONALLIGHT_H
#define MORDEROPENGLUDEMYTUTORIAL_DIRECTIONALLIGHT_H

#include <map>
#include "../../Common/CommonValues.h"
#include "../../Core/Entities/LightEntity.h"

class DirectionalLight : public LightEntity {

public:
    DirectionalLight();

    DirectionalLight(
    		glm::vec3 color,
    		glm::vec3 direction,
    		GLfloat ambientIntensity, GLfloat diffuseIntensity,
    		GLfloat shadowWidth, GLfloat shadowHeight,
			glm::mat4 lightProj);

    ~DirectionalLight() override;

	void UseLight(Shader* shader) override;
	
    static void SetupUniforms(std::map<std::string, GLint>& m_uniforms,GLuint shaderProgram);

private:

    glm::vec3 direction;

};


#endif //MORDEROPENGLUDEMYTUTORIAL_DIRECTIONALLIGHT_H
