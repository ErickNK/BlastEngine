//
// Created by erick on 9/19/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_LIGHTROTATIONCOMPONENT_H
#define MORDEROPENGLUDEMYTUTORIAL_LIGHTROTATIONCOMPONENT_H

#include "../../../Rendering/Lighting/PointLight.h"

class LightRotationComponent : public EntityComponent<LightEntity> {
public:
    void Update(double time, float delta) override {
        m_entity->getTransform().Rotate(glm::vec3(0,glm::degrees(.00001f),0));
    }
};


#endif //MORDEROPENGLUDEMYTUTORIAL_LIGHTROTATIONCOMPONENT_H
