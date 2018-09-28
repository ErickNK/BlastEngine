//
// Created by erick on 8/23/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_LIGHT_H
#define MORDEROPENGLUDEMYTUTORIAL_LIGHT_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Core/Entities/LightEntity.h"
#include "../../Common/CommonValues.h"
#include "../PostProcessing/FrameBufferObject.h"
#include "Shadow.h"

class CoreEngine;

class Light : public LightEntity{
public:
    Light(LightType lightType);

    Light(LightType lightType,glm::vec3 color,GLfloat ambientIntensity, GLfloat diffuseIntensity, GLfloat shadowWidth, GLfloat shadowHeight);

    virtual ~Light();

	FrameBufferObject GetShadowMapFBO() { return m_shadow.shadow_map_fbo; }

	Shadow& GetShadow() { return m_shadow; }

    GLuint GetShadowMapTexture() { return m_shadow.shadow_map_texture; }

	const glm::vec3 &getColor() const;

	GLfloat getAmbientIntensity() const;

    LightType getType() const;

    bool isCellShadingOn() const;

    void setAllowCellShading(bool m_allow_cell_shading);

protected:

    glm::vec3 color;

    GLfloat ambientIntensity;

	GLfloat diffuseIntensity;

	LightType m_type;

	Shadow m_shadow;

	//TODO improve cell shading
	bool m_allow_cell_shading = false;

	int m_cell_shading_level = 2;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_LIGHT_H
