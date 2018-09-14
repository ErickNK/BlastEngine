//
// Created by erick on 9/9/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_FOG_H
#define MORDEROPENGLUDEMYTUTORIAL_FOG_H


#include <glm/glm.hpp>
#include "../Core/Entities/EffectEntity.h"
#include "../Core/Components/RenderingComponents/FogComponent.h"

class Fog : public EffectEntity{
public:
    Fog(glm::vec4 color, float fogDensity, float fogGradient):
    EffectEntity(), m_color(color),m_fogDensity(fogDensity),m_fogGradient(fogGradient){
        auto * fogComponent = new FogComponent();
        this->AddComponent(fogComponent);
    };
    glm::vec4 m_color;
    float m_fogDensity;
    float m_fogGradient;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_FOG_H
