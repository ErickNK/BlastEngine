#include "ShadowMap.h"

ShadowMap::ShadowMap() :
	m_frameBufferObject(0),
	m_shadowMapTexture(0) {}

ShadowMap::~ShadowMap()
{
	if (m_frameBufferObject) glDeleteFramebuffers(1, &m_frameBufferObject);
	if (m_shadowMapTexture) glDeleteTextures(1, &m_shadowMapTexture);
	m_frameBufferObject = m_shadowMapTexture = m_shadowHeight = m_shadowWidth = 0;
}

bool ShadowMap::Init(GLuint width, GLuint height)
{
	m_shadowHeight = height;
	m_shadowWidth = width;

	glGenFramebuffers(1, &m_frameBufferObject); //Create the shadow-map framebuffer
	
	glGenTextures(1, &m_shadowMapTexture); //Create shadow-map texture
	glBindTexture(GL_TEXTURE_2D, m_shadowMapTexture);

		//WRAP filter
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//Overlap filter
		glTexParameterf(
			GL_TEXTURE_2D,
			GL_TEXTURE_MIN_FILTER, // Applied when texture is further away/smaller
			GL_LINEAR_MIPMAP_LINEAR
		);
		glTexParameterf(
			GL_TEXTURE_2D,
			GL_TEXTURE_MAG_FILTER, // Applied when texture is closer/bigger
			GL_LINEAR
		);

		//Data
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_DEPTH_COMPONENT,
			m_shadowWidth, m_shadowHeight,
			0,
			GL_DEPTH_COMPONENT,
			GL_FLOAT,
			nullptr
		);

		glBindFramebuffer(GL_FRAMEBUFFER,m_frameBufferObject); //Bind buffer for both drawing and reading

			glFramebufferTexture2D( //Tells buffer to draw its contents to a out shadow-map texture.
				GL_FRAMEBUFFER,
				GL_DEPTH_ATTACHMENT, // Tells buffer to write only depth data.
				GL_TEXTURE_2D,
				m_shadowMapTexture,
				0
			); 
			// No reading or drawing color
			glDrawBuffer(GL_NONE);
			glReadBuffer(GL_NONE);

			GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
			if (status != GL_FRAMEBUFFER_COMPLETE) {
				printf("Framebuffer Error: &i\n", status);
				return false;
			}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

void ShadowMap::BindFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferObject); //Bind shadow buffer.
}

void ShadowMap::UnBindFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0); //unBind shadow buffer.
}

void ShadowMap::UseShadowMap(GLenum textureUnit)
{
	// Activate the texture unit the texture is to load into
	glActiveTexture(GL_TEXTURE0 + textureUnit);

	// Bind the texture for use
	glBindTexture(GL_TEXTURE_2D, m_shadowMapTexture);
}
