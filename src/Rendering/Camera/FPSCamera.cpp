//
// Created by erick on 9/11/18.
//

#include "FPSCamera.h"

FPSCamera::FPSCamera() {}

FPSCamera::FPSCamera(glm::vec3 startPosition, glm::vec3 startUp,
        GLfloat startYaw, GLfloat startPitch,GLfloat startRoll,
        GLfloat startMovementSpeed, GLfloat startTurningSpeed) :
        Camera(startPosition,startUp,startYaw,startPitch,startMovementSpeed,startTurningSpeed)
{
    m_transform.SetPos(startPosition);
//    m_transform.SetPos(startPosition);

    UpdateView();
}
//void FPSCamera::UpdateView()
//{
//
//    //roll can be removed from here. because is not actually used in FPS camera
//    glm::mat4 matRoll  = glm::mat4(1.0f);//identity matrix;
//    glm::mat4 matPitch = glm::mat4(1.0f);//identity matrix
//    glm::mat4 matYaw   = glm::mat4(1.0f);//identity matrix
//
//    //roll, pitch and yaw are used to store our angles in our class
//    matRoll  = glm::rotate(matRoll,  m_roll,  glm::vec3(0.0f, 0.0f, 1.0f));
//    matPitch = glm::rotate(matPitch, m_pitch, glm::vec3(1.0f, 0.0f, 0.0f));
//    matYaw   = glm::rotate(matYaw,  m_yaw,    glm::vec3(0.0f, 1.0f, 0.0f));
//
//    //order matters
//    glm::mat4 rotate = matRoll * matPitch * matYaw;
//
//    glm::mat4 translate = glm::mat4(1.0f);
//    translate = glm::translate(translate, -m_transform.GetPos());
//
//    m_viewMatrix = rotate * translate;
//}

void FPSCamera::UpdateView()
{
    //temporary frame quaternion from pitch,yaw,roll
    //here roll is not used
    glm::quat key_quat = glm::quat(glm::vec3(m_pitch, m_yaw, m_roll));
    //reset values
    m_pitch = m_yaw = m_roll = 0;

    //order matters,update camera_quat
    m_transform.GetRot() = key_quat * m_transform.GetRot(); //Multiply the new quat by the old one
    m_transform.GetRot() = m_transform.GetRot();
//    glm::mat4 rotate = glm::mat4_cast(m_transform.GetRot());

//    glm::mat4 translate = glm::mat4(1.0f);
//    translate = glm::translate(translate, -m_transform.GetPos());

    m_forward = glm::normalize(m_transform.GetForward()); //remove magnitude
    m_right = glm::normalize(glm::cross(m_forward,m_worldUp));
    m_up = glm::normalize(glm::cross(m_right,m_forward));

    m_viewMatrix = glm::lookAt(m_transform.GetPos(), m_transform.GetPos() + m_forward, m_up);
//    m_viewMatrix = rotate * translate;
}

void FPSCamera::ProcessInput(Input *input, float delta) {
    handleMouse(input->getXChange(),input->getYChange());
    handleKeys(input->getKeys(),delta);
    UpdateView();
}

void FPSCamera::handleKeys(const bool *keys, GLfloat deltaTime) {

    GLfloat velocity = m_movementSpeed * deltaTime;

    float dx = 0; //how much we strafe on x
    float dz = 0; //how much we walk on z

    if(keys[GLFW_KEY_W]){
        dz = 2;
    }

    if(keys[GLFW_KEY_D]){
        dx = 2;
    }

    if(keys[GLFW_KEY_S]){
        dz = -2;
    }

    if(keys[GLFW_KEY_A]){
        dx = -2;
    }


    //row major
    glm::vec3 forward(m_viewMatrix[0][2], m_viewMatrix[1][2], m_viewMatrix[2][2]);
    glm::vec3 strafe( m_viewMatrix[0][0], m_viewMatrix[1][0], m_viewMatrix[2][0]);

    //forward vector must be negative to look forward.
    //read :http://in2gpu.com/2015/05/17/view-matrix/
    m_transform.GetPos() += (-dz * forward + dx * strafe) * velocity;
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

Transform FPSCamera::getTransform()  {
    return m_transform;
}

