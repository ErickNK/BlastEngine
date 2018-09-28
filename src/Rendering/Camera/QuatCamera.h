//
// Created by erick on 9/27/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_QUATCAMERA_H
#define MORDEROPENGLUDEMYTUTORIAL_QUATCAMERA_H

#include <iostream>
#include "Camera.h"

class QuatCamera : public Camera{
public:
    QuatCamera(): Camera() {}

    QuatCamera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch,
            GLfloat startMovementSpeed, GLfloat startTurningSpeed)
            : Camera(startPosition,startUp,startYaw,startPitch,startMovementSpeed,startTurningSpeed){ m_transform.LookAt(glm::vec3(0.0,1.0,0.0)); };

    void UpdateView() override {

        //Pitch locally
        glm::quat qPitch = glm::angleAxis(-m_pitch, m_transform.GetRight());
        //Yaw globally
        glm::quat qYaw = glm::angleAxis(-m_yaw, m_worldUp);

        //For a FPS camera we can omit roll
        glm::quat orientation = qPitch * qYaw;

        m_transform.SetRot(glm::normalize(orientation));

        m_look_at = m_transform.GetPos() + m_transform.GetForward() * 1.0f;

        m_viewMatrix = glm::lookAt(m_transform.GetPos(), m_look_at, m_transform.GetUp());
    }

    void UpdateViewWithoutTurn(Transform transform){
        this->m_transform = transform;

        m_look_at = m_transform.GetPos() + m_transform.GetForward() * 1.0f;

        m_viewMatrix = glm::lookAt(m_transform.GetPos(), m_look_at, m_transform.GetUp());
    }

    void handleKeys(const bool *keys, GLfloat deltaTime) override{

        GLfloat mvelocity = m_movementSpeed * deltaTime;
        GLfloat tvelocity = m_turnSpeed * deltaTime;

        if(keys[GLFW_KEY_W]){
            m_transform.GetPos() += m_transform.GetForward() * mvelocity;
        }

        if(keys[GLFW_KEY_D]){
            m_transform.GetPos() -= m_transform.GetRight() * mvelocity;
        }

        if(keys[GLFW_KEY_S]){
            m_transform.GetPos() -= m_transform.GetForward() * mvelocity;
        }

        if(keys[GLFW_KEY_A]){
            m_transform.GetPos() += m_transform.GetRight() * mvelocity;
        }

        if(keys[GLFW_KEY_UP]){
            m_transform.GetPos() += m_transform.GetUp() * mvelocity;
        }

        if(keys[GLFW_KEY_DOWN]){
            m_transform.GetPos() -= m_transform.GetUp() * mvelocity;
        }

        if(keys[GLFW_KEY_LEFT]){
            m_yaw -= glm::degrees(50.0) * tvelocity;
        }

        if(keys[GLFW_KEY_RIGHT]){
            m_yaw += glm::degrees(50.0) * tvelocity;
        }
    }

    void handleMouse(double xChange, double yChange) override{

        xChange *= m_turnSpeed;
        yChange *= m_turnSpeed;

        m_yaw += xChange;
        m_pitch += yChange;

        if(m_pitch > 0.99f){
            m_pitch = 0.99f;
        }

        if(m_pitch < -0.99f){
            m_pitch = -0.99f;
        }
    }

};


#endif //MORDEROPENGLUDEMYTUTORIAL_QUATCAMERA_H
