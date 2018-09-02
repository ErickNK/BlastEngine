#pragma once

#include <stdio.h>
#include "GL/glew.h"
class ShadowMap {
public:
	ShadowMap();
	
	~ShadowMap();

	virtual bool Init(GLuint width, GLuint height);

	/*
	* Write to our shadow-map texture. Binds the shadow-map's frameBufferObject ready to
	* write to the shadow-map texture.
	*/
	virtual void BindFrameBuffer();
	virtual void UnBindFrameBuffer();

	/*
	* Sets the shadow-map to be used for drawing shadows.
	*/
	virtual void UseShadowMap(GLenum textureUnit);

	//GETTERS
	GLuint GetShadowWidth() { return m_shadowWidth; }
	GLuint GetShadowHeight() { return m_shadowHeight; }

protected:
	GLuint m_frameBufferObject, m_shadowMapTexture;
	GLuint m_shadowWidth, m_shadowHeight;
};