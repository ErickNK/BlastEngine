//
// Created by erick on 8/21/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_CAMERA_H
#define MORDEROPENGLUDEMYTUTORIAL_CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {

public:
    Camera();

    Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch,
           GLfloat startMovementSpeed, GLfloat startTurningSpeed);

    virtual ~Camera();

    void handleKeys(const bool *keys, GLfloat deltaTime);

    void handleMouse(double xChange, double yChange);

    glm::mat4 getViewMatrix() const;

	void setViewMatrix(glm::mat4x4 viewMatrix);

    glm::vec3 getPosition() const;

    glm::vec3 getDirection() const;

protected:
private:
    /**
    * The position of the camera
    * */
    glm::vec3 m_position;
    glm::vec3 m_forward;
    glm::vec3 m_right;
    glm::vec3 m_up;

    glm::vec3 m_worldUp;

    GLfloat m_yaw;
    GLfloat m_pitch;

    GLfloat m_movementSpeed;
    GLfloat m_turnSpeed;

	glm::mat4 m_viewMatrix;

    void updateAngle();
};


#endif //MORDEROPENGLUDEMYTUTORIAL_CAMERA_H
