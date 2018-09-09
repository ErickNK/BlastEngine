//
// Created by erick on 8/24/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_MATERIAL_H
#define MORDEROPENGLUDEMYTUTORIAL_MATERIAL_H

#include <GL/glew.h>
#include "Shaders/Shader.h"
#include "Texture.h"

class Material {
public:
    Material();

	Material(GLfloat specularIntensity, GLfloat shininess);
	
	Material(GLfloat specularIntensity, GLfloat shininess, std::vector<Texture>& textures);

    virtual ~Material();

	void UseMaterial(Shader * shader) ;

	static void SetupUniforms(std::map<std::string, GLint>& m_uniforms,GLuint shaderProgram);

	void setSpecularIntensity(GLfloat specularIntensity);

	void setShininess(GLfloat shininess);
private:
	std::vector<Texture> textures;
    GLfloat specularIntensity;
    GLfloat shininess;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_MATERIAL_H
