//
// Created by erick on 8/23/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_LIGHT_H
#define MORDEROPENGLUDEMYTUTORIAL_LIGHT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

class Light {
public:
    Light();

    Light(glm::vec3 color,GLfloat ambientIntensity, GLfloat diffuseIntensity);

    virtual ~Light();

protected:
    glm::vec3 color;

    GLfloat ambientIntensity;

    GLfloat diffuseIntensity;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_LIGHT_H
