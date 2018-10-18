//
// Created by erick on 9/14/18.
//

#include "TPSCameraAttachment.h"
#include "../../../Rendering/Camera/TPSCamera.h"

void TPSCameraAttachment::ProcessInput(Input *input, float delta) {
    float horizontalDistance = m_entity->CalculateHorizontalDistance();
    float verticalDistance = m_entity->CalculateVerticalDistnace();
    double angle_around_change = m_entity->angle_around_attachment - oldAngle_around_attachment;
    if(angle_around_change != 0) {
        m_entity->setYaw(180 - static_cast<float>(m_entity->getTransform().GetRot().y +  m_entity->angle_around_attachment ));
    }

    float theta = m_entity->getTransform().GetRot().y + m_entity->angle_around_attachment;
    float offsetX = horizontalDistance * sin(glm::radians(theta));
    float offsetZ = horizontalDistance * cos(glm::radians(theta));
    m_entity->setXPos(m_entity->getTransform().GetPos().x - offsetX);
    m_entity->setZPos(m_entity->getTransform().GetPos().z - offsetZ);
    m_entity->setYPos(m_entity->getTransform().GetPos().y + verticalDistance + 10.0f);

    oldAngle_around_attachment = m_entity->angle_around_attachment;
}

void TPSCameraAttachment::SetAttachment(Entity* entity) {
    m_attached_entity = entity;
}