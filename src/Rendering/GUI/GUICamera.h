//
// Created by erick on 9/15/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_GUICAMERA_H
#define MORDEROPENGLUDEMYTUTORIAL_GUICAMERA_H


#include "../Camera/Camera.h"

class GUICamera : Camera{
    GUICamera();

    GUICamera(glm::vec3 startPosition, glm::vec3 startUp,
            GLfloat startYaw, GLfloat startPitch,
            GLfloat startMovementSpeed, GLfloat startTurningSpeed);
};


#endif //MORDEROPENGLUDEMYTUTORIAL_GUICAMERA_H
