//
// Created by erick on 8/24/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_POINTLIGHT_H
#define MORDEROPENGLUDEMYTUTORIAL_POINTLIGHT_H

#include "Light.h"
#include "../Core/CommonValues.h"

class PointLight : public Light {

public:
    PointLight();

    PointLight(int id, glm::vec3 color, glm::vec3 position,
            GLfloat ambientIntensity, GLfloat diffuseIntensity,
            GLfloat constant, GLfloat linear, GLfloat quadratic,
			GLfloat shadowWidth, GLfloat shadowHeight);

    ~PointLight() override;

    void UseLight(PointLightUniforms *pointLightUniforms, int shadowTextureUnit);

	static void SetupUniforms(PointLightUniforms *pointLightUniforms, GLuint shaderProgram);

protected:
    int id;

    glm::vec3 position;

    GLfloat constant, linear, quadratic;

};


#endif //MORDEROPENGLUDEMYTUTORIAL_POINTLIGHT_H
