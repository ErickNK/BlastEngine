#include <utility>

//
// Created by erick on 8/24/18.
//

#include "Material.h"
#include "Loaders/MeshedLoader.h"
#include "TextureAtlas.h"

Material::Material() :
    specularIntensity(0.0f),
    shininess(0.0f) {}

Material::Material(GLfloat specularIntensity, GLfloat shininess): 
	specularIntensity(specularIntensity),
	shininess(shininess) {}

Material::Material(GLfloat specularIntensity, GLfloat shininess, std::vector<Texture*>& textures) :
	textures(textures),
    specularIntensity(specularIntensity),
    shininess(shininess) {}

Material::Material(float specularIntensity, float shininess, std::vector<Texture*>& textures,  bool* options):
        textures(std::move(textures)),
        specularIntensity(specularIntensity),
        shininess(shininess),
        hasTransparency(options[Transparency]),
        hasFakeLighting(options[FakeLighting]){}
Material::~Material() {}

void Material::UseMaterial(Shader * shader) {
    unsigned int diffuseNr = 0;
    unsigned int specularNr = 0;
    shader->Uniform1i("material.diffuseTextureCount", 0);
    shader->Uniform1i("material.specularTextureCount", 0);

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        auto textureUnit = static_cast<unsigned int>(shader->getAvailableDrawingTextureUnit());
        TextureTypeEnum type = textures[i]->GetTextureType();
        char locBuff[100] = { '\0' };

        if (type == DIFFUSE_TEXTURE) {
            if (diffuseNr == MAX_MATERIALS_TEXTURES) return;

            //Set Diffuse texture texture-unit
            snprintf(locBuff, sizeof(locBuff), "material.diffuse_texture[%d]", i);

            shader->Uniform1i(locBuff, textureUnit);
            diffuseNr++;
            shader->Uniform1i("material.diffuseTextureCount", diffuseNr);

            //DEFAULTS
            shader->Uniform1i("textureAtlasNumOfRows",1);
            shader->Uniform2f("textureAtlasOffset",0.0f,0.0f);
        }
        else if (type == SPECULAR_TEXTURE)
        {
            if (specularNr == MAX_MATERIALS_TEXTURES) return;

            //Set Diffuse texture texture-unit
            snprintf(locBuff, sizeof(locBuff), "material.specular_texture[%d]", i);

            shader->Uniform1i(locBuff, textureUnit);
            specularNr++;
            shader->Uniform1i("material.specularTextureCount", specularNr);

            //DEFAULTS
            shader->Uniform1i("textureAtlasNumOfRows",1);
            shader->Uniform2f("textureAtlasOffset",0.0f,0.0f);

        }else if (type == DIFFUSE_TEXTURE_ATLAS){

            if (diffuseNr == MAX_MATERIALS_TEXTURES) return;

            //Set Diffuse texture texture-unit
            snprintf(locBuff, sizeof(locBuff), "material.diffuse_texture[%d]", i);

            shader->Uniform1i(locBuff, textureUnit);
            diffuseNr++;
            shader->Uniform1i("material.diffuseTextureCount", diffuseNr);

            shader->Uniform1i("textureAtlasNumOfRows",
                    ((TextureAtlas*)(textures[i]))->getNumberOfRows());
            shader->Uniform2f("textureAtlasOffset",
                    ((TextureAtlas*)(textures[i]))->getTextureXOffset(),
                    ((TextureAtlas*)(textures[i]))->getTextureYOffset());
        }else if (type == SPECULAR_TEXTURE_ATLAS){

            if (specularNr == MAX_MATERIALS_TEXTURES) return;

            //Set Diffuse texture texture-unit
            snprintf(locBuff, sizeof(locBuff), "material.specular_texture[%d]", i);

            shader->Uniform1i(locBuff, textureUnit);
            specularNr++;
            shader->Uniform1i("material.specularTextureCount", specularNr);

            shader->Uniform1i("textureAtlasNumOfRows",
                        ((TextureAtlas*)(textures[i]))->getNumberOfRows());
            shader->Uniform2f("textureAtlasOffset",
                        ((TextureAtlas*)(textures[i]))->getTextureXOffset(),
                        ((TextureAtlas*)(textures[i]))->getTextureYOffset());
        }

        //Bind texture to texture-unit i
        textures[i]->Bind(textureUnit);
    }

    //Set Specular Intensity
    shader->Uniform1f("material.specularIntensity",specularIntensity);

    //Set Shininess
    shader->Uniform1f("material.shininess",shininess);

    //Set has transparency
    if(hasTransparency){
        glDisable(GL_CULL_FACE);
    }
    shader->Uniform1i("material.hasTransparency",hasTransparency);

    shader->Uniform1i("hasFakeLighting",hasFakeLighting);

    GLenum someError = glGetError();
    assert( someError == GL_NO_ERROR);
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

	//Create transparency check
	m_uniforms["material.hasTransparency"] = glGetUniformLocation(shaderProgram, "material.hasTransparency");

    //Create fakeLighting check
	m_uniforms["hasFakeLighting"] = glGetUniformLocation(shaderProgram, "hasFakeLighting");

    //Create Atlas support
    m_uniforms["textureAtlasNumOfRows"] = glGetUniformLocation(shaderProgram, "textureAtlasNumOfRows");

    //Create Atlas support
    m_uniforms["textureAtlasOffset"] = glGetUniformLocation(shaderProgram, "textureAtlasOffset");
}

void Material::setSpecularIntensity(GLfloat s) {
    specularIntensity = s;
}

void Material::setShininess(GLfloat s) {
    shininess = s;
}

std::vector<Texture*> &Material::getTextures() {
    return textures;
}

void Material::setHasTransparency(bool hasTransparency) {
    Material::hasTransparency = hasTransparency;
}

bool& Material::isHasTransparency() {
    return hasTransparency;
}

