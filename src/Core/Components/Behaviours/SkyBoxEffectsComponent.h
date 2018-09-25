//
// Created by erick on 9/15/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_SKYBOXEFFECTSCOMPONENT_H
#define MORDEROPENGLUDEMYTUTORIAL_SKYBOXEFFECTSCOMPONENT_H

#include "../../../Rendering/RenderingEngine.h"
#include "../../../Rendering/Shaders/SkyBoxShader.h"
#include "../EntityComponent.h"
#include "../../../Common/Time.h"

class SkyBoxEffectsComponent: public EntityComponent<SkyBox,RenderingEngine> {
public:
    void Update(double time, float delta) override {
        m_entity->setBlendFactor(static_cast<float>(Time::GetGameWorldTime()));
        m_entity->getTransform().Rotate(glm::vec3(0,glm::degrees(.00001f) * m_entity->getRotationSpeed(),0));
    }

};


#endif //MORDEROPENGLUDEMYTUTORIAL_SKYBOXEFFECTSCOMPONENT_H
