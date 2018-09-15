//
// Created by erick on 8/23/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_LIGHT_H
#define MORDEROPENGLUDEMYTUTORIAL_LIGHT_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShadowMap.h"
#include "../../Core/Entities/LightEntity.h"
#include "../../Common/CommonValues.h"

class CoreEngine;

class Light : public LightEntity{
public:
    Light(LightType lightType);

    Light(LightType lightType,glm::vec3 color,GLfloat ambientIntensity, GLfloat diffuseIntensity, GLfloat shadowWidth, GLfloat shadowHeight);

    virtual ~Light();

	ShadowMap* GetShadowMap() { return shadowMap; }

	const glm::vec3 &getColor() const;

	GLfloat getAmbientIntensity() const;

    LightType getType() const;

    bool isCellShadingOn() const;

    void setAllowCellShading(bool m_allow_cell_shading);

protected:

    glm::vec3 color;

    GLfloat ambientIntensity;

	GLfloat diffuseIntensity;

	glm::mat4 lightProjection;

	glm::mat4 lightSpace;

	ShadowMap* shadowMap;

	LightType m_type;

	//TODO improve cell shading
	bool m_allow_cell_shading = false;

	int m_cell_shading_level = 2;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_LIGHT_H
