//
// Created by erick on 9/13/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_TPCATTACHMENT_H
#define MORDEROPENGLUDEMYTUTORIAL_TPCATTACHMENT_H


#include "../../Entities/MeshedEntity.h"

class TPSCamera;

class TPSCameraAttachment : public EntityComponent<TPSCamera>{
public:
    TPSCameraAttachment() : EntityComponent(TPS_CAMERA_ATTACHEMENT) {}

    explicit TPSCameraAttachment(Entity *entity):
    EntityComponent(TPS_CAMERA_ATTACHEMENT),
    m_attached_entity(entity) {}

    void ProcessInput(Input *input, float delta) override;

    void SetAttachment(Entity* entity);

private:
    Entity* m_attached_entity = nullptr;

    double oldAngle_around_attachment = 0;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_TPCATTACHMENT_H
