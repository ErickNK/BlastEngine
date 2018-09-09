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

void Material::UseMaterial(Shader * shader) {
    unsigned int diffuseNr = 0;
    unsigned int specularNr = 0;
    glUniform1i(shader->getUniforms()["material.diffuseTextureCount"], 0);
    glUniform1i(shader->getUniforms()["material.specularTextureCount"], 0);

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        auto textureUnit = static_cast<unsigned int>(shader->getAvailableDrawingTextureUnit());
        TextureTypeEnum type = textures[i].GetTextureType();
        char locBuff[100] = { '\0' };

        if (type == DIFFUSE_TEXTURE) {
            if (diffuseNr == MAX_MATERIALS_TEXTURES) return;

            //Set Diffuse texture texture-unit
            snprintf(locBuff, sizeof(locBuff), "material.diffuse_texture[%d]", i);

            glUniform1i(shader->getUniforms()[locBuff], textureUnit);
            diffuseNr++;
            glUniform1i(shader->getUniforms()["material.diffuseTextureCount"], diffuseNr);
        }
        else if (type == SPECULAR_TEXTURE)
        {
            if (specularNr == MAX_MATERIALS_TEXTURES) return;

            //Set Diffuse texture texture-unit
            snprintf(locBuff, sizeof(locBuff), "material.specular_texture[%d]", i);

            glUniform1i(shader->getUniforms()[locBuff], textureUnit);
            specularNr++;
            glUniform1i(shader->getUniforms()["material.specularTextureCount"], specularNr);
        }

        //Bind texture to texture-unit i
        textures[i].Bind(textureUnit);
    }

    //Set Specular Intensity
    glUniform1f(shader->getUniforms()["material.specularIntensity"],specularIntensity);

    //Set Shininess
    glUniform1f(shader->getUniforms()["material.shininess"],shininess);
}

void Material::SetupUniforms(std::map<std::string, GLint>& m_uniforms,GLuint shaderProgram) {

	m_uniforms["material.diffuseTextureCount"] = glGetUniformLocation(shaderProgram, "material.diffuseTextureCount");

	m_uniforms["material.specularTextureCount"] = glGetUniformLocation(shaderProgram, "material.specularTextureCount");

	for (size_t i = 0; i < MAX_MATERIALS_TEXTURES; i++) {

		char locBuff[100] = { '\0' };

		snprintf(locBuff, sizeof(locBuff), "material.diffuse_texture[%d]", i);
		m_uniforms[locBuff] = glGetUniformLocation(shaderProgram, locBuff);

		snprintf(locBuff, sizeof(locBuff), "material.specular_texture[%d]", i);
		m_uniforms[locBuff] = glGetUniformLocation(shaderProgram, locBuff);

	}

	//Create Shininess Uniform
	m_uniforms["material.shininess"] = glGetUniformLocation(shaderProgram, "material.shininess");

	//Create Specular Intensity Uniform
	m_uniforms["material.specularIntensity"] = glGetUniformLocation(shaderProgram, "material.specularIntensity");
}

void Material::setSpecularIntensity(GLfloat s) {
    specularIntensity = s;
}

void Material::setShininess(GLfloat s) {
    shininess = s;
}

