//
// Created by erick on 9/10/18.
//

#include "LightEntity.h"
#include "../Components/RenderingComponents/ShadowRendererComponent.h"

LightEntity::LightEntity(LightType lightType):
        m_type(lightType),
        color(glm::vec3(1.0f,1.0f,1.0f)),
        ambientIntensity(1.0f),
        diffuseIntensity(0.0f) {}

LightEntity::LightEntity(
        LightType lightType,
        glm::vec3 color,
        GLfloat ambientIntensity, GLfloat diffuseIntensity,
        GLfloat shadowWidth, GLfloat shadowHeight) :
        m_type(lightType),
        color(color),
        ambientIntensity(ambientIntensity),
        diffuseIntensity(diffuseIntensity)
{}

LightEntity::~LightEntity() {}

void LightEntity::ProcessInput(Input* input, float delta)
{
//    m_transform.Update();

    for (auto &m_component : m_light_components) {
        m_component->ProcessInput(input, delta);
    }
}

void LightEntity::Update(double time, float delta)
{
    for (auto &m_component : m_light_components) {
        m_component->Update(time, delta);
    }

    for (auto m_component : m_shadow_components) {
        m_component->Update(time, delta);
    }
}

void LightEntity::RenderLight(RenderingEngine* engine) const
{
    for (auto m_component : m_light_components) {
        m_component->Render(engine);
    }
}

void LightEntity::RenderShadow(RenderingEngine* engine) const
{
    for (auto m_component : m_shadow_components) {
        m_component->Render(engine);
    }
}

LightEntity *LightEntity::AddComponent(EntityComponent<LightEntity> *component) {
    m_light_components.push_back(component);
    component->SetParent(this);
    return this;
}

LightEntity* LightEntity::AddShadowComponent(ShadowRendererComponent *component) {
    m_shadow_components.push_back(component);
    component->SetParent(this);
    return this;
}

const glm::vec3 &LightEntity::getColor() const {
    return color;
}

GLfloat LightEntity::getAmbientIntensity() const {
    return ambientIntensity;
}

LightType LightEntity::getType() const {
    return m_type;
}

bool LightEntity::isCellShadingOn() const {
    return m_allow_cell_shading;
}

void LightEntity::setAllowCellShading(bool m_allow_cell_shading) {
    LightEntity::m_allow_cell_shading = m_allow_cell_shading;
}

int LightEntity::getId() const {
    return m_id;
}

void LightEntity::setId(int id) {
    LightEntity::m_id = id;
}

