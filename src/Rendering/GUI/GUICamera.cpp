//
// Created by erick on 9/15/18.
//

#include "GUICamera.h"
GUICamera::GUICamera():Camera() {}

GUICamera::GUICamera(glm::vec3 startPosition, glm::vec3 startUp,
                     GLfloat startYaw, GLfloat startPitch,
                     GLfloat startMovementSpeed, GLfloat startTurningSpeed) :
        Camera(startPosition,startUp,startYaw,startPitch,startMovementSpeed,startTurningSpeed)
{
    m_transform.SetPos(startPosition);
    m_forward = glm::vec3(0.0f,0.0f,0.0f);
    UpdateView();
}