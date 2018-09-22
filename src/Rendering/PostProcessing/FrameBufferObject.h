//
// Created by erick on 9/21/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_FRAMEBUFFEROBJECT_H
#define MORDEROPENGLUDEMYTUTORIAL_FRAMEBUFFEROBJECT_H


#include <stdio.h>
#include "GL/glew.h"

//TODO: make FrameBufferObject reusable for making shadow-maps
class FrameBufferObject {
public:
    FrameBufferObject();

    ~FrameBufferObject();

    virtual bool Init(GLuint width, GLuint height, GLenum type, GLenum attachment, GLenum component);

    virtual void setForReading(bool color, int unit) const;

    virtual void setForDrawing(bool color, int unit) const;

    bool checkForErrors() const;

    /*
    * Write to our texture. Binds the frameBufferObject ready to
    * write to the texture.
    */
    virtual void BindFrameBuffer() const;
    virtual void UnBindFrameBuffer() const;

    /*
    * Sets the shadow-map to be used for drawing shadows.
    */
    virtual void UseTexture(GLenum textureUnit) const;

    //GETTERS
    GLuint GetWidth() { return m_width; }
    GLuint GetHeight() { return m_height; }
    GLuint GetTexture() { return m_texture; }
    GLuint GetFrameBuffer() { return m_frameBufferObject; }
protected:
    GLuint m_frameBufferObject, m_texture;
    GLuint m_width, m_height;
    GLenum m_type, m_attachment, m_component;

    virtual void setOverlayFilter();

    virtual void setWrapFilter();

    virtual void setData();

    virtual void attachTexture();
};


#endif //MORDEROPENGLUDEMYTUTORIAL_FRAMEBUFFEROBJECT_H
