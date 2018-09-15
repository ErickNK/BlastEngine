//
// Created by erick on 8/23/18.
//

#include "Light.h"

Light::Light(LightType lightType):
        LightEntity(),
		m_type(lightType),
		color(glm::vec3(1.0f,1.0f,1.0f)),
		ambientIntensity(1.0f),
		diffuseIntensity(0.0f) {}

Light::Light(
		LightType lightType,
		glm::vec3 color,
		GLfloat ambientIntensity, GLfloat diffuseIntensity,
		GLfloat shadowWidth, GLfloat shadowHeight) :
		LightEntity(),
		m_type(lightType),
		color(color),
		ambientIntensity(ambientIntensity),
		diffuseIntensity(diffuseIntensity)
{
	shadowMap = new ShadowMap();
	shadowMap->Init(shadowWidth,shadowHeight);
}

Light::~Light() {}

const glm::vec3 &Light::getColor() const {
    return color;
}

GLfloat Light::getAmbientIntensity() const {
    return ambientIntensity;
}

LightType Light::getType() const {
    return m_type;
}

bool Light::isCellShadingOn() const {
	return m_allow_cell_shading;
}

void Light::setAllowCellShading(bool m_allow_cell_shading) {
	Light::m_allow_cell_shading = m_allow_cell_shading;
}
