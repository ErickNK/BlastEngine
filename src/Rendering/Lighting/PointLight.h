//
// Created by erick on 8/24/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_POINTLIGHT_H
#define MORDEROPENGLUDEMYTUTORIAL_POINTLIGHT_H

#include "Light.h"
#include <map>
#include "../../Common/CommonValues.h"

class PointLight : public Light {

public:
    PointLight();

    PointLight(glm::vec3 color, glm::vec3 position,
            GLfloat ambientIntensity, GLfloat diffuseIntensity,
            GLfloat constant, GLfloat linear, GLfloat quadratic,
			GLfloat shadowWidth, GLfloat shadowHeight);

    ~PointLight() override;

    virtual void UseLight(std::map<std::string, GLint>& m_uniforms, int shadowTextureUnit);

	static void SetupUniforms(std::map<std::string, GLint>& m_uniforms, GLuint shaderProgram);

    void AddToEngine(CoreEngine *engine) override;
protected:
    int id;

    glm::vec3 position;

    GLfloat constant, linear, quadratic;

};


#endif //MORDEROPENGLUDEMYTUTORIAL_POINTLIGHT_H
