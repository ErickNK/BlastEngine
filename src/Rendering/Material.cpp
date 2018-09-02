//
// Created by erick on 8/24/18.
//

#include "Material.h"

Material::Material() :
    specularIntensity(0.0f),
    shininess(0.0f) {}

Material::Material(GLfloat specularIntensity, GLfloat shininess): 
	specularIntensity(specularIntensity),
	shininess(shininess) {}

Material::Material(GLfloat specularIntensity, GLfloat shininess, std::vector<Texture>& textures) :
	textures(textures),
    specularIntensity(specularIntensity),
    shininess(shininess) {}

Material::~Material() {}

void Material::UseMaterial(Shader* shader) {
	unsigned int diffuseNr = 0;
	unsigned int specularNr = 0;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		int textureUnit = shader->getAvailableDrawingTextureUnit();
		TextureTypeEnum type = textures[i].GetTextureType();
		if (type == DIFFUSE_TEXTURE) {
			if (diffuseNr == 16) return;

			//Set Diffuse texture texture-unit
			glUniform1i(shader->getMaterialUniforms()->diffuse_texture_u[i], textureUnit);
			diffuseNr++;
			glUniform1i(shader->getMaterialUniforms()->diffuse_texture_count_u, diffuseNr);
		}
		else if (type == SPECULAR_TEXTURE)
		{
			if (specularNr == 16) return;

			//Set Diffuse texture texture-unit
			glUniform1i(shader->getMaterialUniforms()->specular_texture_u[i], textureUnit);
			specularNr++;
			glUniform1i(shader->getMaterialUniforms()->specular_texture_count_u, specularNr);
		}
		
		//Bind texture to texture-unit i
		textures[i].Bind(textureUnit);
	}
	
	//Set Specular Intensity
    glUniform1f(shader->getMaterialUniforms()->specular_intensity_u,specularIntensity);

    //Set Shininess
    glUniform1f(shader->getMaterialUniforms()->shininess_u,shininess);
}

void Material::SetupUniforms(MaterialUniforms *materialUniforms,GLuint shaderProgram) {
	
	materialUniforms->diffuse_texture_count_u = glGetUniformLocation(shaderProgram, "material.diffuseTextureCount");

	materialUniforms->specular_texture_count_u = glGetUniformLocation(shaderProgram, "material.specularTextureCount");

	for (size_t i = 0; i < MAX_MATERIALS_TEXTURES; i++) {

		char locBuff[100] = { '\0' };

		snprintf(locBuff, sizeof(locBuff), "material.diffuse_texture[%d]", i);
		materialUniforms->diffuse_texture_u[i] = glGetUniformLocation(shaderProgram, locBuff);

		snprintf(locBuff, sizeof(locBuff), "material.specular_texture[%d]", i);
		materialUniforms->specular_texture_u[i] = glGetUniformLocation(shaderProgram, locBuff);

	}

	//Create Shininess Uniform
    materialUniforms->shininess_u = glGetUniformLocation(shaderProgram, "material.shininess");

    //Create Specular Intensity Uniform
    materialUniforms->specular_intensity_u = glGetUniformLocation(shaderProgram, "material.specularIntensity");
}
