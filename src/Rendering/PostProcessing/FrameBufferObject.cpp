//
// Created by erick on 9/21/18.
//

#include <cassert>
#include "FrameBufferObject.h"

FrameBufferObject::FrameBufferObject() :
        m_frameBufferObject(0),
        m_texture(0) {}

FrameBufferObject::~FrameBufferObject()
{
    if (m_frameBufferObject) glDeleteFramebuffers(1, &m_frameBufferObject);
    if (m_texture) glDeleteTextures(1, &m_texture);
    m_frameBufferObject = m_texture = m_height = m_width = 0;
}

void FrameBufferObject::setOverlayFilter() {
    //Overlap filter
    glTexParameteri(
            m_type,
            GL_TEXTURE_MIN_FILTER, // Applied when texture is further away/smaller
            GL_LINEAR_MIPMAP_LINEAR
    );
    glTexParameteri(
            m_type,
            GL_TEXTURE_MAG_FILTER, // Applied when texture is closer/bigger
            GL_LINEAR
    );
}

void FrameBufferObject::setWrapFilter() {
    //WRAP filter
    glTexParameteri(m_type, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(m_type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(m_type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColors[]{1.0f,1.0f,1.0f,1.0f};
    glTexParameterfv(m_type,GL_TEXTURE_BORDER_COLOR,borderColors);
}

void FrameBufferObject::setData() {

    if(m_type == GL_TEXTURE_2D){
        //Data
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                m_component,
                m_width, m_height,
                0,
                m_component,
                GL_FLOAT,
                nullptr
        );
    }else if( m_type == GL_TEXTURE_CUBE_MAP){
        for(size_t i = 0; i < 6; i++){
            //Data
            glTexImage2D(
                    GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                    0,
                    m_component,
                    m_width, m_height,
                    0,
                    m_component,
                    GL_FLOAT,
                    nullptr
            );
        }
    }
}

void FrameBufferObject::attachTexture() {
    glFramebufferTexture2D( //Tells buffer to draw its contents to an out texture.
            GL_FRAMEBUFFER,
            m_attachment, // Tells buffer to write only depth data.
            m_type,
            m_texture,
            0
    );
}


bool FrameBufferObject::Init(GLuint width, GLuint height,GLenum type, GLenum attachment,GLenum component)
{
    m_height = height;
    m_width = width;
    m_type = type;
    m_attachment = attachment;
    m_component = component;

    glGenFramebuffers(1, &m_frameBufferObject); //Create the framebuffer

    glGenTextures(1, &m_texture); //Create texture

    glBindTexture(m_type, m_texture);

        setWrapFilter();

        setOverlayFilter();

        setData();

        attachTexture();

    glBindTexture(m_type, 0);

    return checkForErrors();
}

void FrameBufferObject::BindFrameBuffer() const
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_frameBufferObject); //Bind shadow buffer.
}

void FrameBufferObject::UnBindFrameBuffer() const
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); //unBind shadow buffer.
}

void FrameBufferObject::UseTexture(GLenum textureUnit) const {
    assert(textureUnit >= 0 && textureUnit < GL_MAX_TEXTURE_UNITS);

    // Activate the texture unit the texture is to load into
    glActiveTexture(GL_TEXTURE0 + textureUnit);

    // Bind the texture for use
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

void FrameBufferObject::setForReading(bool color, int unit) const {
    if (!color) {
        glReadBuffer(GL_NONE);
        return;
    }

    assert(unit >= 0 && unit < GL_MAX_COLOR_ATTACHMENTS);
    glReadBuffer(GL_COLOR_ATTACHMENT0 + unit);

}

void FrameBufferObject::setForDrawing(bool color, int unit) const {
    if (!color) {
        glDrawBuffer(GL_NONE);
        return;
    }

    assert(unit >= 0 && unit < GL_MAX_COLOR_ATTACHMENTS);
    glDrawBuffer(GL_COLOR_ATTACHMENT0 + unit);
}

bool FrameBufferObject::checkForErrors() const {
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        printf("Framebuffer Error: &i\n", status);

        return false;
    }

    return true;
}
