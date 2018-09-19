//
// Created by erick on 9/13/18.
//

#include "TPSCamera.h"

void TPSCamera::UpdateView()
{

    //detmine axis for pitch rotation
    m_right = glm::normalize(glm::cross(m_forward, m_up));
    //compute quaternion for pitch based on the camera pitch angle
    glm::quat pitch_quat = glm::angleAxis(m_pitch, m_right);
    //determine heading quaternion from the camera up vector and the heading angle
    glm::quat heading_quat = glm::angleAxis(m_yaw, m_up);
    //add the two quaternions
    glm::quat temp = glm::cross(pitch_quat, heading_quat);
    temp = glm::normalize(temp);
    //update the direction from the quaternion
    m_forward = glm::rotate(temp, m_forward);
    //set the look at to be infront of the camera
    m_look_at = m_transform.GetPos() + m_forward * 1.0f;
    //damping for smooth camera
    m_yaw *= .5;
    m_pitch *= .5;

    m_viewMatrix = glm::lookAt(m_transform.GetPos(), m_look_at, m_up);
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
    auto pitchChange = static_cast<float>(input->getYChange() * m_turnSpeed);
    m_pitch = pitchChange;
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
    m_yaw = d * angle_around_speed;
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
    m_forward = glm::normalize(m_component->getMeshedEntity()->getTransform().GetPos() - m_transform.GetPos());

}

void TPSCamera::setForward(glm::vec3 forward) {
    m_forward = forward;
}

void TPSCamera::setTransform(Transform &transform) {
    m_transform = transform;
}

void TPSCamera::setLookAt(glm::vec3 lookat) {
    m_look_at = lookat;
}
