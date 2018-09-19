//
// Created by erick on 9/13/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_TPCATTACHMENT_H
#define MORDEROPENGLUDEMYTUTORIAL_TPCATTACHMENT_H


#include "../../Entities/MeshedEntity.h"

class TPSCamera;

class TPSCameraAttachment {
public:
    TPSCameraAttachment() = default;


    TPSCameraAttachment(MeshedEntity *meshedEntity):
    m_meshed_entity(meshedEntity){}

    TPSCameraAttachment(MeshedEntity* meshedEntity, TPSCamera* camera):
    m_meshed_entity(meshedEntity),
    m_camera(camera) {}

    void ProcessInput(Input *input, float delta);

    void Update(float delta);

    void SetAttachment(MeshedEntity* entity);

    void SetCamera(TPSCamera *camera);

    MeshedEntity *getMeshedEntity() const;

private:
    MeshedEntity* m_meshed_entity;
    TPSCamera* m_camera;
    double oldAngle_around_attachment = 0;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_TPCATTACHMENT_H
