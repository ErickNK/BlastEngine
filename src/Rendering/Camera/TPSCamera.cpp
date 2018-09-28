//
// Created by erick on 9/13/18.
//

#include "TPSCamera.h"

void TPSCamera::UpdateView() {

//    //Pitch locally
//    glm::quat qPitch = glm::angleAxis(-m_pitch, m_transform.GetRight());
//    //Yaw globally
//    glm::quat qYaw = glm::angleAxis(-m_yaw, m_worldUp);
//
//    //For a FPS camera we can omit roll
//    glm::quat orientation = qPitch * qYaw;
//
//    m_component->getMeshedEntity()->getTransform().SetRot(glm::normalize(orientation));
//
//    m_transform.SetRot(glm::normalize(orientation));

    m_look_at = m_component->getMeshedEntity()->getTransform().GetPos();

    m_viewMatrix = glm::lookAt(m_transform.GetPos(), m_look_at, m_component->getMeshedEntity()->getTransform().GetUp());
//
//    m_look_at = m_transform.GetPos() + m_transform.GetForward() * 1.0f;
//
//    m_viewMatrix = glm::lookAt(m_transform.GetPos(), m_look_at, m_transform.GetUp());
}

void TPSCamera::ProcessInput(Input *input, float delta) {
    CalulateZoom(input);
    CalulatePitch(input);
    CalulateAngleAround(input);
    m_component->ProcessInput(input,delta);
    UpdateView();
}

void TPSCamera::CalulateZoom(Input* input) {
    auto zoomLevel = static_cast<float>(input->getYWheelChange() * zoom_speed);
    distance_from_attachment -= zoomLevel;
}

void TPSCamera::CalulatePitch(Input* input) {
    auto pitchChange = static_cast<float>(input->getYChange() * pitch_angle_speed);
    m_pitch -= pitchChange;
}

void TPSCamera::CalulateAngleAround(Input* input) {
    auto yawChange = static_cast<float>(input->getXChange() * angle_around_speed);
    angle_around_attachment -= yawChange;
}

float TPSCamera::CalculateHorizontalDistance() {
    return distance_from_attachment * cos(glm::radians(m_pitch));
}

float TPSCamera::CalculateVerticalDistnace() {
    return distance_from_attachment * sin(glm::radians(m_pitch));
}

void TPSCamera::setYaw(float d) {
    m_yaw = d;
}

void TPSCamera::setXPos(float d) {
    m_transform.SetXPos(d);
}
void TPSCamera::setZPos(float d) {
    m_transform.SetZPos(d);
}
void TPSCamera::setYPos(float d) {
    m_transform.SetYPos(d);
}

void TPSCamera::Attach(MeshedEntity* meshedEntity) {
    m_component->SetAttachment(meshedEntity);
}

void TPSCamera::SetAttachmentComponent(TPSCameraAttachment *pAttachment) {
    m_component = pAttachment;
    m_component->SetCamera(this);
}