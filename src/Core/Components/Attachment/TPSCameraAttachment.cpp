//
// Created by erick on 9/14/18.
//

#include "TPSCameraAttachment.h"
#include "../../../Rendering/Camera/TPSCamera.h"

void TPSCameraAttachment::ProcessInput(Input *input, float delta) {
    float horizontalDistance = m_camera->CalculateHorizontalDistance();
    float verticalDistance = m_camera->CalculateVerticalDistnace();
    double angle_around_change = m_camera->angle_around_attachment - oldAngle_around_attachment;
    if(angle_around_change != 0) {
        m_camera->setYaw(180 - static_cast<float>(m_meshed_entity->getTransform().GetRot().y +  m_camera->angle_around_attachment ));
    }

    float theta = m_meshed_entity->getTransform().GetRot().y + m_camera->angle_around_attachment;
    float offsetX = horizontalDistance * sin(glm::radians(theta));
    float offsetZ = horizontalDistance * cos(glm::radians(theta));
    m_camera->setXPos(m_meshed_entity->getTransform().GetPos().x - offsetX);
    m_camera->setZPos(m_meshed_entity->getTransform().GetPos().z - offsetZ);
    m_camera->setYPos(m_meshed_entity->getTransform().GetPos().y + verticalDistance + 10.0f);

    oldAngle_around_attachment = m_camera->angle_around_attachment;
}

void TPSCameraAttachment::Update(double time, float delta) {

}

void TPSCameraAttachment::SetAttachment(MeshedEntity* entity) {
    m_meshed_entity = entity;
}

void TPSCameraAttachment::SetCamera(TPSCamera *camera) {
    m_camera = camera;
}

MeshedEntity *TPSCameraAttachment::getMeshedEntity() const {
    return m_meshed_entity;
}

