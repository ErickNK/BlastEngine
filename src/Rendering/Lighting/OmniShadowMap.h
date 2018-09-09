//
// Created by erick on 9/6/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_OMNISHADOWMAP_H
#define MORDEROPENGLUDEMYTUTORIAL_OMNISHADOWMAP_H


#include "ShadowMap.h"

class OmniShadowMap : ShadowMap{

    OmniShadowMap();
    ~OmniShadowMap();

    bool Init(GLuint width, GLuint height) override;

    /*
    * Write to our shadow-map texture. Binds the shadow-map's frameBufferObject ready to
    * write to the shadow-map texture.
    */
    void BindFrameBuffer() override;
    void UnBindFrameBuffer() override;

    /*
    * Sets the shadow-map to be used for drawing shadows.
    */
    void UseShadowMap(GLenum textureUnit) override;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_OMNISHADOWMAP_H
