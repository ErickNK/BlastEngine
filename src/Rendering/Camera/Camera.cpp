//
// Created by erick on 8/21/18.
//

#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>

Camera::Camera() {

}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch,
        GLfloat startMovementSpeed, GLfloat startTurningSpeed) :
        m_worldUp(startUp), m_yaw(startYaw), m_pitch(startPitch),
        m_movementSpeed(startMovementSpeed), m_turnSpeed(startTurningSpeed){
    m_transform.SetPos(startPosition);
    m_forward = glm::vec3(0.0f,0.0f,0.0f);
    UpdateView();
}

Camera::~Camera() {

}

void Camera::UpdateView() {
    m_forward.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_forward.y = sin(glm::radians(m_pitch));
    m_forward.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_forward = glm::normalize(m_forward); //remove magnitude

    m_right = glm::normalize(glm::cross(m_forward,m_worldUp));

    m_up = glm::normalize(glm::cross(m_right,m_forward));

    m_look_at = m_transform.GetPos() + m_forward * 1.0f;

	m_viewMatrix = glm::lookAt(m_transform.GetPos(), m_look_at, m_up);
//    m_projection = glm::perspective(field_of_view, aspect, near_clip, far_clip);

}

void Camera::ProcessInput(Input *input, float delta) {
    handleMouse(input->getXChange(),input->getYChange());
    handleKeys(input->getKeys(),delta);
    UpdateView();
}

void Camera::handleKeys(const bool *keys, GLfloat deltaTime) {

    GLfloat velocity = m_movementSpeed * deltaTime;

    if(keys[GLFW_KEY_W]){
        m_transform.GetPos() += m_forward * velocity;
    }

    if(keys[GLFW_KEY_D]){
        m_transform.GetPos() += m_right * velocity;
    }

    if(keys[GLFW_KEY_S]){
        m_transform.GetPos() -= m_forward * velocity;
    }

    if(keys[GLFW_KEY_A]){
        m_transform.GetPos() -= m_right * velocity;
    }

    if(keys[GLFW_KEY_UP]){
        m_transform.GetPos() += m_up * velocity;
    }

    if(keys[GLFW_KEY_DOWN]){
        m_transform.GetPos() -= m_up * velocity;
    }
}

void Camera::LookAt(glm::vec3 point)  {
//    glm::vec3 lookVector = glm::vec3(x, y, z);
//    assert(lookVector != position);
//
//    glm::vec3 direction = glm::normalize(lookVector-position);
//    float dot = glm::dot(glm::vec3(0, 0, 1), direction);
//    if (fabs(dot - (-1.0f)) < 0.000001f) {
//        rotation = glm::angleAxis(RadiansToDegrees(M_PI), glm::vec3(0, 1, 0));
//        return;
//    }
//    else if (fabs(dot - (1.0f)) < 0.000001f) {
//        rotation = glm::quat();
//        return;
//    }
//
//    float angle = -RadiansToDegrees(acosf(dot));
//
//    glm::vec3 cross = glm::normalize(glm::cross(glm::vec3(0, 0, 1), direction));
//    rotation = glm::normalize(glm::angleAxis(angle, cross));
}


glm::mat4 Camera::getViewMatrix() const {
	return m_viewMatrix;
}

void Camera::setViewMatrix(glm::mat4x4 viewMatrix) {
	m_viewMatrix = viewMatrix;
}

void Camera::handleMouse(double xChange, double yChange) {

    xChange *= m_turnSpeed;
    yChange *= m_turnSpeed;

    m_yaw += xChange;
    m_pitch += yChange;

    if(m_pitch > 89.0f){
        m_pitch = 89.0f;
    }

    if(m_pitch < -89.0f){
        m_pitch = -89.0f;
    }
}

glm::vec3 Camera::getDirection() const {
    return glm::normalize(m_forward);
}

Transform Camera::getTransform()  const{
    return m_transform;
}

glm::mat4 Camera::getProjection() const{
    return m_projection;
}


