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

    Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch,
           GLfloat startMovementSpeed, GLfloat startTurningSpeed,float field_of_view, float aspect, float near_clip, float far_clip);

    virtual ~Camera();

	virtual void ProcessInput(Input* input, float delta);

    virtual void Update(float delta){};

	virtual void handleKeys(const bool *keys, GLfloat deltaTime);

	virtual void handleMouse(double xChange, double yChange);

    virtual void LookAt(glm::vec3 point) ;

    glm::mat4 getViewMatrix() const;

	void setViewMatrix(glm::mat4x4 viewMatrix);

    glm::vec3 getDirection() const;

    Transform getTransform() const;

    void setProjection(float field_of_view, float aspect, float near_clip, float far_clip);

    void setProjection(glm::mat4 projection);

    const glm::mat4& getProjection() const;

    void setAllowMovement(bool allow);

    void setAllowTurn(bool turn);

    virtual void UpdateView();

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

	bool allow_move = true;
	bool allow_turn = true;

    glm::mat4 m_projection;

public:
	float field_of_view =  45.0f;
	float aspect = 1366.0f/786.0f;
	float near_clip = 0.1f;
	float far_clip = 1000.0f;

    void invertPitch();
};


#endif //MORDEROPENGLUDEMYTUTORIAL_CAMERA_H
