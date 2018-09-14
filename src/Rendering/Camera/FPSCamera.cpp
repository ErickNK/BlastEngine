//
// Created by erick on 9/11/18.
//

#include "FPSCamera.h"

FPSCamera::FPSCamera() {}

FPSCamera::FPSCamera(glm::vec3 startPosition, glm::vec3 startUp,
        GLfloat startYaw, GLfloat startPitch,GLfloat startRoll,
        GLfloat startMovementSpeed, GLfloat startTurningSpeed) :
        Camera(startPosition,startUp,startYaw,startPitch,startMovementSpeed,startTurningSpeed)
{}

void FPSCamera::UpdateView()
{
//    m_forward = glm::normalize(m_look_at - m_transform.GetPos());

    //detmine axis for pitch rotation
    m_right = glm::normalize(glm::cross(m_forward, m_up));
    //compute quaternion for pitch based on the camera pitch angle
    glm::quat pitch_quat = glm::angleAxis(m_pitch, m_right);
    //determine heading quaternion from the camera up vector and the heading angle
    glm::quat heading_quat = glm::angleAxis(-m_yaw, m_up);
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

void FPSCamera::handleMouse(double xChange, double yChange) {

    xChange *= m_turnSpeed;
    yChange *= m_turnSpeed;

    m_yaw = xChange;
    m_pitch = yChange;

    if(m_pitch > 89.0f){
        m_pitch = 89.0f;
    }

    if(m_pitch < -89.0f){
        m_pitch = -89.0f;
    }
}

void FPSCamera::LookAt(glm::vec3 point) {
    m_look_at = point;

    assert(m_look_at != m_transform.GetPos()); //Not looking at self.

    m_forward = glm::normalize(m_look_at - m_transform.GetPos());

    float dot = glm::dot(glm::vec3(0, 0, 1), m_forward);
    if (fabs(dot - (-1.0f)) < 0.000001f) {
        m_transform.SetRot(glm::angleAxis((float)glm::degrees(glm::radians(M_PI)), glm::vec3(0, 1, 0)));
        return;
    }
    else if (fabs(dot - (1.0f)) < 0.000001f) {
        m_transform.SetRot(glm::quat());
        return;
    }

    float angle = - glm::degrees(glm::radians(acosf(dot)));

    glm::vec3 cross = glm::normalize(glm::cross(glm::vec3(0, 0, 1), m_forward));
    m_transform.SetRot(glm::normalize(glm::angleAxis(angle, cross)));
}

void FPSCamera::LookAt(MeshedEntity* entity) {
    LookAt(entity->getTransform().GetPos());
}

