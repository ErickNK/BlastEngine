//
// Created by erick on 8/24/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_POINTLIGHT_H
#define MORDEROPENGLUDEMYTUTORIAL_POINTLIGHT_H

#include "Light.h"
#include "CommonValues.h"

class PointLight : public Light {

public:
    PointLight();

    PointLight(int id, glm::vec3 color, glm::vec3 position,
            GLfloat ambientIntensity, GLfloat diffuseIntensity,
            GLfloat constant, GLfloat linear, GLfloat quadratic);

    ~PointLight() override;

    void UseLight(PointLightUniforms *pointLightUniforms);

protected:
    int id;

    glm::vec3 position;

    GLfloat constant, linear, quadratic;

};


#endif //MORDEROPENGLUDEMYTUTORIAL_POINTLIGHT_H
