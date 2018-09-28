#include <cmath>

//
// Created by erick on 9/28/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_SPHEREMOVEMENT_H
#define MORDEROPENGLUDEMYTUTORIAL_SPHEREMOVEMENT_H


#include "../Rendering/Lighting/Light.h"
#include "../Rendering/Lighting/DirectionalLight.h"

class LightMovement : public EntityComponent<Light,RenderingEngine> {
public:
    void Update(double time, float delta) override {

        m_entity->getTransform().Rotate(glm::vec3(0,angle * 0.00001f,0));
//        dynamic_cast<DirectionalLight *>(m_entity)->getTransform().GetPos().x = 0.0f + std::cos(angle) * radius;
//        dynamic_cast<DirectionalLight *>(m_entity)->getTransform().GetPos().z = 0.0f + std::sin(angle) * radius;
    }

private:
    float angle = 20.0f;
    float radius = 50.0f;
};

#endif //MORDEROPENGLUDEMYTUTORIAL_SPHEREMOVEMENT_H
