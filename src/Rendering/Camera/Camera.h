//
// Created by erick on 8/21/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_CAMERA_H
#define MORDEROPENGLUDEMYTUTORIAL_CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../../Core/Input.h"
#include "../Transform.h"

class Camera {

public:
    Camera();

    Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch,
           GLfloat startMovementSpeed, GLfloat startTurningSpeed);

    virtual ~Camera();

	virtual void ProcessInput(Input* input, float delta);

	virtual void handleKeys(const bool *keys, GLfloat deltaTime);

	virtual void handleMouse(double xChange, double yChange);

    virtual void LookAt(glm::vec3 point) ;

    glm::mat4 getViewMatrix() const;

	void setViewMatrix(glm::mat4x4 viewMatrix);

    glm::vec3 getDirection() const;

    Transform getTransform() const;

    glm::mat4 getProjection() const;

protected:
    /**
    * The position of the camera
    * */
    glm::vec3 m_look_at;
    glm::vec3 m_forward;
    glm::vec3 m_right;
    glm::vec3 m_up;

    glm::vec3 m_worldUp;

    GLfloat m_yaw;
    GLfloat m_pitch;

    GLfloat m_movementSpeed;
    GLfloat m_turnSpeed;

    Transform m_transform = Transform();
	glm::mat4 m_viewMatrix;

    glm::mat4 m_projection;
    int viewport_x;
    int viewport_y;
    int window_width;
    int window_height;

	virtual void UpdateView();
};


#endif //MORDEROPENGLUDEMYTUTORIAL_CAMERA_H
