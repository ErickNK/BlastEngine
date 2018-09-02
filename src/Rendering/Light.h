//
// Created by erick on 8/23/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_LIGHT_H
#define MORDEROPENGLUDEMYTUTORIAL_LIGHT_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shadows/ShadowMap.h"

class Light {
public:
    Light();

    Light(glm::vec3 color,GLfloat ambientIntensity, GLfloat diffuseIntensity, GLfloat shadowWidth, GLfloat shadowHeight);

    virtual ~Light();

	ShadowMap* GetShadowMap() { return shadowMap; }

protected:
    glm::vec3 color;

    GLfloat ambientIntensity;

    GLfloat diffuseIntensity;

	glm::mat4 lightProjection;

	glm::mat4 lightSpace;

	ShadowMap* shadowMap;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_LIGHT_H
