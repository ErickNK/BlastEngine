//
// Created by erick on 9/21/18.
//

#include <cassert>
#include "FrameBufferObject.h"

FrameBufferObject::FrameBufferObject() :
        m_frameBufferObject(0),
        m_width(0),
        m_height(0){ glGenFramebuffers(1, &m_frameBufferObject); }

FrameBufferObject::~FrameBufferObject()
{
//    if (m_frameBufferObject) glDeleteFramebuffers(1, &m_frameBufferObject);
//    for(GLuint& texture: m_textures) glDeleteTextures(1, &texture);
//    for(GLuint& renderBuffer: m_renderBuffers) glDeleteRenderbuffers(1, &renderBuffer);
//    m_frameBufferObject = m_height = m_width = 0;
}

void FrameBufferObject::setOverlayFilter() {
    if(m_texture_options[m_texture_count][ENABLE_OVERLAY_FILTER] == GL_TRUE){
        //Overlap filter
        glTexParameteri(
                m_texture_options[m_texture_count][TEXTURE_TYPE],
                GL_TEXTURE_MIN_FILTER, // Applied when texture is further away/smaller
                m_texture_options[m_texture_count][OVERLAY_FILTER]
        );
        glTexParameteri(
                m_texture_options[m_texture_count][TEXTURE_TYPE],
                GL_TEXTURE_MAG_FILTER, // Applied when texture is closer/bigger
                m_texture_options[m_texture_count][OVERLAY_FILTER]
        );
    }
}

void FrameBufferObject::setWrapFilter() {
    if(m_texture_options[m_texture_count][ENABLE_WRAP_FILTER] == GL_TRUE){
        //WRAP filter
        if(m_texture_options[m_texture_count][TEXTURE_TYPE] == GL_TEXTURE_CUBE_MAP)
            glTexParameteri(m_texture_options[m_texture_count][TEXTURE_TYPE], GL_TEXTURE_WRAP_R, m_texture_options[m_texture_count][WRAP_FILTER]);

        glTexParameteri(m_texture_options[m_texture_count][TEXTURE_TYPE], GL_TEXTURE_WRAP_S, m_texture_options[m_texture_count][WRAP_FILTER]);
        glTexParameteri(m_texture_options[m_texture_count][TEXTURE_TYPE], GL_TEXTURE_WRAP_T, m_texture_options[m_texture_count][WRAP_FILTER]);

        if(m_texture_options[m_texture_count][WRAP_FILTER] == GL_CLAMP_TO_BORDER){
            float borderColors[]{1.0f,1.0f,1.0f,1.0f};
            glTexParameterfv(m_texture_options[m_texture_count][TEXTURE_TYPE],GL_TEXTURE_BORDER_COLOR,borderColors);
        }
    }
}

void FrameBufferObject::setTextureData() {

    if(m_texture_options[m_texture_count][TEXTURE_TYPE] == GL_TEXTURE_2D){
        //Data
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                m_texture_options[m_texture_count][INTERNAL_COMPONENT_FORMAT],
                m_width, m_height,
                0,
                m_texture_options[m_texture_count][EXTERNAL_COMPONENT_FORMAT],
                GL_UNSIGNED_BYTE,
                nullptr
        );
    }else if( m_texture_options[m_texture_count][TEXTURE_TYPE] == GL_TEXTURE_CUBE_MAP){
        for(size_t i = 0; i < 6; i++){
            //Data
            glTexImage2D(
                    GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                    0,
                    m_texture_options[m_texture_count][INTERNAL_COMPONENT_FORMAT],
                    m_width, m_height,
                    0,
                    m_texture_options[m_texture_count][EXTERNAL_COMPONENT_FORMAT],
                    GL_UNSIGNED_BYTE,
                    nullptr
            );
        }
    }
}

void FrameBufferObject::attachTexture() {
    glFramebufferTexture2D( //Tells buffer to draw its contents to an out texture.
            GL_FRAMEBUFFER,
            m_texture_options[m_texture_count][ATTACHMENT_TYPE],
            m_texture_options[m_texture_count][TEXTURE_TYPE],
            m_textures[m_texture_count],
            0 //Level of mipmap of texture to use
    );
}

void FrameBufferObject::setRenderBufferStorage(){
    glRenderbufferStorage(
            m_render_buffer_options[m_render_buffer_count][TYPE],
            m_render_buffer_options[m_render_buffer_count][EXTERNAL_COMPONENT_FORMAT],
            m_width, m_height
    );
}

void FrameBufferObject::attachRenderBuffer(){
    glFramebufferRenderbuffer( //Tells buffer to draw its contents to an out texture.
            GL_FRAMEBUFFER,
            m_render_buffer_options[m_render_buffer_count][ATTACHMENT_TYPE],
            m_render_buffer_options[m_render_buffer_count][TYPE],
            m_renderBuffers[m_render_buffer_count]
    );
}

void FrameBufferObject::CreateFBORenderBuffer() {
    glGenRenderbuffers(1, &m_renderBuffers[m_render_buffer_count]); //Create texture

    glBindRenderbuffer(m_render_buffer_options[m_render_buffer_count][TYPE], m_renderBuffers[m_render_buffer_count]);

        setRenderBufferStorage();

        attachRenderBuffer();

    glBindRenderbuffer(m_render_buffer_options[m_render_buffer_count][TYPE], 0);
}

void FrameBufferObject::CreateFBOTexture(){
    glGenTextures(1, &m_textures[m_texture_count]); //Create texture

    glBindTexture(m_texture_options[m_texture_count][TEXTURE_TYPE], m_textures[m_texture_count]);

        setWrapFilter();

        setOverlayFilter();

        setTextureData();

        attachTexture();

    glBindTexture(m_texture_options[m_texture_count][TEXTURE_TYPE], 0);
}

bool FrameBufferObject::Generate(GLuint &id, GLuint width, GLuint height, GLenum* options)
{
    m_width = width;
    m_height = height;

    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferObject); //Bind shadow buffer.

        bool status = false;

        if(options[TYPE] == GL_TEXTURE){
            m_texture_count++;
            if(m_texture_count >= 32) return false;

            id = m_texture_count;
            std::copy(options, options + NUM_FBO_OPTIONS, m_texture_options[m_texture_count]);

            CreateFBOTexture();
            status = checkForErrors();
        }else if(options[TYPE] == GL_RENDERBUFFER){
            m_render_buffer_count++;
            if(m_render_buffer_count >= 32) return false;

            id = m_render_buffer_count;
            std::copy(options, options + NUM_FBO_OPTIONS, m_render_buffer_options[m_render_buffer_count]);

            CreateFBORenderBuffer();
            status = checkForErrors();
        }

    glBindFramebuffer(GL_FRAMEBUFFER, 0); //unBind shadow buffer.
    return status;
}

void FrameBufferObject::BindFrameBuffer() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferObject); //Bind shadow buffer.
    glViewport(0,0,m_width,m_height);
}

void FrameBufferObject::UnBindFrameBuffer(GLuint displayWidth, GLuint displayHeight) const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0); //unBind shadow buffer.
    glViewport(0,0,displayWidth,displayHeight);
}

void FrameBufferObject::UseTexture(int id, GLenum textureUnit) const {
    GLenum someError1 = glGetError();
    assert( someError1 == GL_NO_ERROR);

    assert(textureUnit >= 0 && textureUnit < GL_MAX_TEXTURE_UNITS);

    // Activate the texture unit the texture is to load into
    glActiveTexture(GL_TEXTURE0 + textureUnit);

    // Bind the texture for use
    glBindTexture(m_texture_options[id][TEXTURE_TYPE], m_textures[id]);

    GLenum someError = glGetError();
    assert( someError == GL_NO_ERROR);
}

void FrameBufferObject::setForReading(bool color, int unit) {
    checkForErrors();

    if (!color) {
        glReadBuffer(GL_NONE); //Read from depth attachment
        return;
    }

    assert(unit >= 0 && unit < GL_MAX_COLOR_ATTACHMENTS);

    glReadBuffer(GL_COLOR_ATTACHMENT0 + unit);

    m_current_reading_unit = unit;

    checkForErrors();
}

void FrameBufferObject::setForReading(bool color, GLenum unit) const {
    checkForErrors();

    if (!color) {
        glReadBuffer(GL_NONE); //Read from depth attachment
        return;
    }

    glReadBuffer(unit);

    checkForErrors();
}

void FrameBufferObject::setForDrawing(bool color, std::vector<GLenum>& buffers) const {
    checkForErrors();

    if (!color) {
        glDrawBuffer(GL_NONE); //Draw to depth attachment
        return;
    }

    this->m_current_drawing_units = buffers;

    glDrawBuffers(buffers.size(),&buffers[0]);

    checkForErrors();
}

bool FrameBufferObject::checkForErrors() const {
    GLenum someError = glGetError();
    assert( someError == GL_NO_ERROR);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        printf("Framebuffer Error: %i \n", status);

        return false;
    }

    return true;
}
