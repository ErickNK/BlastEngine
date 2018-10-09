//
// Created by erick on 9/13/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_TPCATTACHMENT_H
#define MORDEROPENGLUDEMYTUTORIAL_TPCATTACHMENT_H


#include "../../Entities/MeshedEntity.h"

class TPSCamera;

class TPSCameraAttachment : public EntityComponent<Entity>{
public:
    TPSCameraAttachment() = default;


    explicit TPSCameraAttachment(Entity *entity){
        m_entity = entity;
    }

    TPSCameraAttachment(Entity* entity, TPSCamera* camera):
    m_camera(camera) {
        m_entity = entity;
    }

    void ProcessInput(Input *input, float delta) override;

    void Update(double time, float delta) override;

    void SetAttachment(Entity* entity);

    void SetCamera(TPSCamera *camera);

    TPSCamera* getCamera();

private:
    TPSCamera* m_camera = nullptr;
    double oldAngle_around_attachment = 0;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_TPCATTACHMENT_H
