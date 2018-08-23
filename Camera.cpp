//
// Created by erick on 8/21/18.
//

#include "Camera.h"

Camera::Camera() {

}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch,
        GLfloat startMovementSpeed, GLfloat startTurningSpeed) :
    m_position(startPosition), m_worldUp(startUp), m_yaw(startYaw), m_pitch(startPitch),
    m_movementSpeed(startMovementSpeed), m_turnSpeed(startTurningSpeed){

    m_forward = glm::vec3(0.0f,0.0f,-1.0f);
    updateAngle();
}

Camera::~Camera() {

}

void Camera::updateAngle() {
    m_forward.x = static_cast<float>(cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)));
    m_forward.y = static_cast<float>(sin(glm::radians(m_pitch)));
    m_forward.z = static_cast<float>(sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)));
    m_forward = glm::normalize(m_forward); //remove magnitude

    m_right = glm::normalize(glm::cross(m_forward,m_worldUp));

    m_up = glm::normalize(glm::cross(m_right,m_forward));
}

void Camera::handleKeys(const bool *keys, GLfloat deltaTime) {

    GLfloat velocity = m_movementSpeed * deltaTime;

    if(keys[GLFW_KEY_W]){
        m_position += m_forward * velocity;
    }

    if(keys[GLFW_KEY_D]){
        m_position += m_right * velocity;
    }

    if(keys[GLFW_KEY_S]){
        m_position -= m_forward * velocity;
    }

    if(keys[GLFW_KEY_A]){
        m_position -= m_right * velocity;
    }

}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(m_position,m_position + m_forward , m_up);
}

void Camera::handleMouse(double xChange, double yChange) {

    xChange *= m_turnSpeed;
    yChange *= m_turnSpeed;

    m_yaw += xChange;
    m_pitch += yChange;

    if(m_pitch > 89.0f){
        m_pitch = 89.0f;
    }

    if(m_pitch > -89.0f){
        m_pitch = -89.0f;
    }

    updateAngle();
}

