//
// Created by erick on 9/15/18.
//

#include "GUIEntity.h"
#include "../Components/GUIComponent.h"
#include "../../Rendering/GUI/GUITexture.h"

GUIEntity::GUIEntity() = default;

GUIEntity::GUIEntity(Transform &transform, GUIMaterial &material)
: m_transform(transform), m_material(material) {}

void GUIEntity::InitMesh(){
    std::vector<glm::vec2> positions;
    positions.emplace_back(-1,1);
    positions.emplace_back(-1,-1);
    positions.emplace_back(1,1);
    positions.emplace_back(1,-1);
    m_GUI_mesh = *new GUIMesh(positions, positions.size());
}

GUIEntity::~GUIEntity()
{
    for (auto &m_component : m_components) {
        delete m_component;
    }
}

void GUIEntity::RenderGUI(RenderingEngine* engine) const
{
    for (auto m_component : m_components) {
        m_component->Render(engine);
    }
}

void GUIEntity::ProcessInput(Input* input, float delta)
{
    m_transform.Update();

    for (auto &m_component : m_components) {
        m_component->ProcessInput(input, delta);
    }
}

void GUIEntity::Update(float delta)
{
    for (auto &m_component : m_components) {
        m_component->Update(delta);
    }
}

GUIEntity* GUIEntity::AddChild(GUIEntity* child)
{
    m_children.push_back(child);
    child->getTransform().SetParent(&m_transform);
    return this;
}

GUIEntity *GUIEntity::AddComponent(GUIComponent *component) {
    m_components.push_back(component);
    component->SetParent(this);
    return this;
}

std::vector<GUIEntity *> &GUIEntity::getChildren() {
    return m_children;
}
