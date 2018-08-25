//
// Created by erick on 8/24/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_MATERIAL_H
#define MORDEROPENGLUDEMYTUTORIAL_MATERIAL_H

#include <GL/glew.h>
#include "Shader.h"

class Material {
public:
    Material();

    Material(GLfloat specularIntensity, GLfloat shininess);

    virtual ~Material();

    void UseMaterial(MaterialUniforms *materialUniforms) ;

    static void SetupUniforms(MaterialUniforms *materialUniforms,GLuint shaderProgram);

private:
    GLfloat specularIntensity;
    GLfloat shininess;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_MATERIAL_H
