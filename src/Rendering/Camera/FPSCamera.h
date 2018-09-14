//
// Created by erick on 9/11/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_FPSCAMERA_H
#define MORDEROPENGLUDEMYTUTORIAL_FPSCAMERA_H

#include "Camera.h"
#include "../Transform.h"
#include "../../Core/Input.h"
#include "../../Core/Entities/MeshedEntity.h"

class FPSCamera : public Camera {

public:

    FPSCamera();

    FPSCamera(glm::vec3 startPosition, glm::vec3 startUp,
            GLfloat startYaw, GLfloat startPitch,GLfloat startRoll,
            GLfloat startMovementSpeed, GLfloat startTurningSpeed);

    void UpdateView() override;

    void handleMouse(double xChange, double yChange) override;

    void LookAt(glm::vec3 point) override;

    void LookAt(MeshedEntity* entity);


};


#endif //MORDEROPENGLUDEMYTUTORIAL_FPSCAMERA_H
