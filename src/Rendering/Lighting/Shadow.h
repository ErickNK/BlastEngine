//
// Created by erick on 9/27/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_SHADOW_H
#define MORDEROPENGLUDEMYTUTORIAL_SHADOW_H

#include "../PostProcessing/FrameBufferObject.h"
#include "../Camera/QuatCamera.h"
#include <glm/glm.hpp>

class Shadow {
public:
    Shadow() = default;

    QuatCamera m_shadow_camera = QuatCamera(
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(0.0f,1.0f,0.0f),
            0.0f,
            0.0f,
            15.0f,
            0.0005f
        );

    glm::mat4 biasMatrix = glm::scale(glm::vec3(0.5,0.5,0.5)) * glm::translate(glm::vec3(1.0,1.0,1.0));

    glm::mat4 lightSpace;

    FrameBufferObject shadow_map_fbo;

    GLuint shadow_map_texture = 0;

    bool m_flipFaces = false;

    float m_bias;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_SHADOW_H
