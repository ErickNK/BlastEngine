//
// Created by erick on 9/12/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_PLAYERMOVEMENT_H
#define MORDEROPENGLUDEMYTUTORIAL_PLAYERMOVEMENT_H

#include <GLFW/glfw3.h>
#include "../EntityComponent.h"
#include "../../../Rendering/Terrain/Terrain.h"

class PlayerMovement : public EntityComponent<MeshedEntity>{

    virtual void ProcessInput(Input* input, float delta) {
//        this->handleKeys(input->getKeys(),delta);
//        this->handleMouse(input->getXChange(),input->getYChange());
    }
    virtual void Update(float delta) {
        //Deal with falling
        upward_speed += gravity * delta;
        m_entity->getTransform().GetPos() += m_entity->getTransform().GetUp() * upward_speed;

        //Terrain Collusion detection
//        terrain_height = m_currentTerrain->getTerrainHeight(
//                    m_entity->getTransform().GetPos().x,
//                    m_entity->getTransform().GetPos().z
//                );

        if(m_entity->getTransform().GetPos().y < terrain_height){
            upward_speed = 0;
            is_in_air = false;
            m_entity->getTransform().GetPos().y = terrain_height;
        }
    }

    virtual void handleKeys(const bool *keys, GLfloat deltaTime) {
        GLfloat movement_velocity = m_movement_speed * deltaTime;
        GLfloat turn_velocity = m_turn_speed * deltaTime;
        GLfloat jump_velocity = jump_power * deltaTime;

        if(keys[GLFW_KEY_W]){
            m_entity->getTransform().GetPos() += m_entity->getTransform().GetForward() * movement_velocity;
        }

        if(keys[GLFW_KEY_D]){
            m_entity->getTransform().GetPos() -= m_entity->getTransform().GetRight() * movement_velocity;
        }

        if(keys[GLFW_KEY_S]){
            m_entity->getTransform().GetPos() -= m_entity->getTransform().GetForward() * movement_velocity;
        }

        if(keys[GLFW_KEY_A]){
            m_entity->getTransform().GetPos() += m_entity->getTransform().GetRight() * movement_velocity;
        }

        if(keys[GLFW_KEY_SPACE]){
//            m_entity->getTransform().GetPos() += m_entity->getTransform().GetUp() * jump_velocity;

            if(!is_in_air){
                upward_speed = jump_velocity;
                is_in_air = true;
            }
        }
    }

    void handleMouse(double xChange, double yChange) {

        xChange *= m_turn_speed;
        yChange *= m_turn_speed;

        m_entity->getTransform().Rotate(xChange,glm::vec3(0,1,0));
    }

private:
    float m_movement_speed = 20;
    float m_turn_speed = 160;
    float jump_power = 50;
    bool is_in_air;
    float upward_speed = 0;
    float gravity = -0.2;

    float terrain_height = 0;
    Terrain* m_currentTerrain;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_PLAYERMOVEMENT_H
