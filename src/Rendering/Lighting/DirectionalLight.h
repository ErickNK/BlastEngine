//
// Created by erick on 8/24/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_DIRECTIONALLIGHT_H
#define MORDEROPENGLUDEMYTUTORIAL_DIRECTIONALLIGHT_H

#include "Light.h"
#include <map>
#include "../../Common/CommonValues.h"

class DirectionalLight : public Light {

public:
    DirectionalLight();

    DirectionalLight(
    		glm::vec3 color,
    		glm::vec3 direction,
    		GLfloat ambientIntensity, GLfloat diffuseIntensity,
    		GLfloat shadowWidth, GLfloat shadowHeight,
			glm::mat4 lightProj);

    ~DirectionalLight() override;

	void SetupLightSpace(std::map<std::string, GLint>& m_uniforms, GLuint shaderProgram);

	void UseLight(std::map<std::string, GLint>& m_uniforms, int shadowTextureUnit);
	
    static void SetupUniforms(std::map<std::string, GLint>& m_uniforms,GLuint shaderProgram);

//    void AddToEngine(CoreEngine *engine) override;

private:

    glm::vec3 direction;

};


#endif //MORDEROPENGLUDEMYTUTORIAL_DIRECTIONALLIGHT_H
