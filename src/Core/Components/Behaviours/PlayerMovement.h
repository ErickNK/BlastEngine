//
// Created by erick on 9/12/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_PLAYERMOVEMENT_H
#define MORDEROPENGLUDEMYTUTORIAL_PLAYERMOVEMENT_H

#include <typeinfo>
#include <GLFW/glfw3.h>
#include "../EntityComponent.h"
#include "../../../Physics/Objects/RigidBody.h"
#include "../Attachment/TPSCameraAttachment.h"
#include "../../../Rendering/Camera/TPSCamera.h"

class PlayerMovement : public EntityComponent<MeshedEntity>{
public:
    void ProcessInput(Input* input, float delta) override {
        mainForce->setAmount(glm::vec3(0,0,0));
        this->handleKeys(input->getKeys(),delta);
    }

    virtual void handleKeys(const bool *keys, GLfloat deltaTime) {
        GLfloat movement_velocity = m_movement_speed * deltaTime;
        GLfloat turn_velocity = m_turn_speed * deltaTime;
        GLfloat jump_velocity = jump_power * deltaTime;

        glm::quat temp = m_entity->getTransform().GetRot();

        glm::vec3 forward = glm::rotate(temp,glm::vec3(0,0,1));
        glm::vec3 right = glm::rotate(temp,glm::vec3(1,0,0));
        glm::vec3 up = glm::rotate(temp,glm::vec3(0,1,0));

        if(keys[GLFW_KEY_W]){
            m_entity->getTransform().GetPos() += forward * movement_velocity;
        }

        if(keys[GLFW_KEY_D]){
            m_entity->getTransform().GetPos() -= right * movement_velocity;
        }

        if(keys[GLFW_KEY_S]){
            m_entity->getTransform().GetPos() -= forward * movement_velocity;
        }

        if(keys[GLFW_KEY_A]){
            m_entity->getTransform().GetPos() += right * movement_velocity;
        }

        if(keys[GLFW_KEY_SPACE]){
            if(!is_in_air){
                mainForce->setAmount(up * jump_power);
                is_in_air = true;
            }
        }
    }

    void SetParent(MeshedEntity *entity) override {
        EntityComponent::SetParent(entity);
        getRigidBody();
    }

    //TODO: Better coordination of components
    void getRigidBody() {
        for (EntityComponent<MeshedEntity>* component: m_entity->getComponents()) {
            if(component->getType() == RIGID_BODY_COMPONENT){
                m_parent_body = reinterpret_cast<RigidBody *>(component);
                m_parent_body->ApplyForce(mainForce);
            }
        }
    }

private:
    float m_movement_speed = 15;
    float m_turn_speed = 0.05;
    float jump_power = 50;
    bool is_in_air = false;
    RigidBody* m_parent_body = nullptr;
    Force* mainForce = new Force();

    TPSCameraAttachment* m_TPS_component = nullptr;

};


#endif //MORDEROPENGLUDEMYTUTORIAL_PLAYERMOVEMENT_H
