//
// Created by erick on 9/13/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_TPSCAMERA_H
#define MORDEROPENGLUDEMYTUTORIAL_TPSCAMERA_H

#include "../../Core/Components/Attachment/TPSCameraAttachment.h"
#include "FPSCamera.h"

class TPSCamera : public FPSCamera{

public:

    TPSCamera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startRoll,
              GLfloat startMovementSpeed, GLfloat startTurningSpeed):
    FPSCamera(startPosition,startUp,startYaw,startPitch,startRoll,startMovementSpeed,startTurningSpeed){}

    void UpdateView() override;
    void ProcessInput(Input* input, float delta) override;

    void Attach(MeshedEntity* meshedEntity);

    void CalulateZoom(Input* input);
    void CalulatePitch(Input* input);
    void CalulateAngleAround(Input* input);
    float CalculateHorizontalDistance();
    float CalculateVerticalDistnace();


    float distance_from_attachment = 50;
    float angle_around_attachment = 0;
    float angle_around_speed = 0.05;
    float zoom_speed = 1;

    TPSCameraAttachment* m_component;

    void setYaw(float d);
    void setXPos(float d);
    void setZPos(float d);
    void setYPos(float d);

    void SetAttachmentComponent(TPSCameraAttachment *pAttachment);
    void setForward(glm::vec3 forward);
    void setLookAt(glm::vec3 lookAt);

    void setTransform(Transform &transform);
};


#endif //MORDEROPENGLUDEMYTUTORIAL_TPSCAMERA_H
