//
// Created by erick on 9/21/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_FRAMEBUFFEROBJECT_H
#define MORDEROPENGLUDEMYTUTORIAL_FRAMEBUFFEROBJECT_H


#include <stdio.h>
#include <vector>
#include "GL/glew.h"
#include "../../Common/CommonValues.h"
#include "../Texture.h"

//TODO: make FrameBufferObject reusable for making shadow-maps
class FrameBufferObject {
public:
    FrameBufferObject();

    ~FrameBufferObject();

    virtual bool Generate(GLuint &id, GLuint width, GLuint height, GLenum* options);

    virtual void setForReading(bool color, int unit);

    virtual void setForReading(bool color, GLenum unit) const;

    virtual void setForDrawing(bool color, std::vector<GLenum>& buffers) const;


    bool checkForErrors() const;

    /*
    * Write to our texture. Binds the frameBufferObject ready to
    * write to the texture.
    */
    virtual void BindFrameBuffer() const;
    virtual void UnBindFrameBuffer(GLuint displayWidth, GLuint displayHeight) const;

    /*
    * Sets the shadow-map to be used for drawing shadows.
    */
    virtual void UseTexture(int id, GLenum textureUnit) const;

    //GETTERS
    GLuint GetWidth() { return m_width; }
    GLuint GetHeight() { return m_height; }
    GLuint* GetTextures() { return m_textures; }
    Texture* GetTexture(int id) const {
        return new Texture(m_textures[id],GUI_TEXTURE);
    }
    GLuint* GetRenderBuffers() { return m_renderBuffers; }
    GLuint GetFrameBuffer() { return m_frameBufferObject; }
protected:

    GLuint m_frameBufferObject, m_textures[32], m_renderBuffers[32];
    GLuint m_width, m_height;
    GLenum m_texture_options[32][NUM_FBO_OPTIONS];
    GLenum m_render_buffer_options[32][NUM_FBO_OPTIONS];
    int m_texture_count = -1, m_render_buffer_count = -1;
    int m_current_drawing_unit = 0, m_current_reading_unit = 0;
    mutable std::vector<GLenum> m_current_drawing_units;
    mutable std::vector<GLenum> m_current_reading_units;
    GLuint m_texture_test;

    virtual void setOverlayFilter();

    virtual void setWrapFilter();

    virtual void setTextureData();

    virtual void attachTexture();

    virtual void CreateFBOTexture();

    virtual void CreateFBORenderBuffer();

    virtual void setRenderBufferStorage();

    virtual void attachRenderBuffer();
};


#endif //MORDEROPENGLUDEMYTUTORIAL_FRAMEBUFFEROBJECT_H
