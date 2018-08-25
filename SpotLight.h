//
// Created by erick on 8/25/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_SPOTLIGHT_H
#define MORDEROPENGLUDEMYTUTORIAL_SPOTLIGHT_H


#include "PointLight.h"

class SpotLight : public PointLight {

public:
    SpotLight();

    SpotLight(
            int id, glm::vec3 color, glm::vec3 position, glm::vec3 direction,
            GLfloat ambientIntensity, GLfloat diffuseIntensity,
            GLfloat constant, GLfloat linear, GLfloat quadratic,
            GLfloat edge
               );

    ~SpotLight() override;

    void UseLight(SpotLightUniforms *spotLightUniforms);

    void SetFlashLight(glm::vec3 position, glm::vec3 direction);

private:

    GLfloat edge, procEdge;

    glm::vec3 direction;

};


#endif //MORDEROPENGLUDEMYTUTORIAL_SPOTLIGHT_H
