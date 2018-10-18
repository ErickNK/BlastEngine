//
// Created by erick on 9/10/18.
//

#include "MeshedEntity.h"

MeshedEntity::MeshedEntity(Mesh &mesh, Transform &transform, Material &material) :
    m_mesh(&mesh), m_material(&material) {}

MeshedEntity::~MeshedEntity()
{
    for (auto &m_component : m_components) {
        delete m_component;
    }

    for (auto &i : m_children) {
        delete i;
    }
}

MeshedEntity* MeshedEntity::AddChild(MeshedEntity* child)
{
    m_children.push_back(child);
    child->getTransform().SetParent(&m_transform);
    return this;
}

MeshedEntity* MeshedEntity::AddComponent(EntityComponent<MeshedEntity>* component)
{
    m_components.push_back(component);
    component->SetParent(this);
    return this;
}

void MeshedEntity::ProcessInputAll(Input* input, float delta)
{
    if(allow_input) {
        ProcessInput(input, delta);

        for (auto &i : m_children) {
            i->ProcessInputAll(input, delta);
        }
    }
}

void MeshedEntity::UpdateAll(double time, float delta)
{
    if(allow_update) {
        Update(time, delta);

        for (auto &i : m_children) {
            i->UpdateAll(time, delta);
        }
    }
}

void MeshedEntity::RenderAll(RenderingEngine* engine) const
{
    if(allow_render) {
        Render(engine);

        for (auto i : m_children) {
            i->RenderAll(engine);
        }
    }
}

void MeshedEntity::ProcessInput(Input* input, float delta)
{
//    m_transform.Update();

    for (auto &m_component : m_components) {
        m_component->ProcessInput(input, delta);
    }
}

void MeshedEntity::Update(double time,float delta)
{
    for (auto &m_component : m_components) {
        m_component->Update(time,delta);
    }
}

void MeshedEntity::Render(RenderingEngine* engine) const
{
    for (auto m_component : m_components) {
        m_component->Render(engine);
    }
}

std::vector<EntityComponent<MeshedEntity> *> &MeshedEntity::getComponents() {
    return m_components;
}

EntityComponent<MeshedEntity> *MeshedEntity::getComponent(ComponentTypes type) const {
    for (auto * component: m_components) {
        if(component->getType() == type){
            return component;
        }
    }
    return nullptr;
}

//std::vector<GameObject*> MeshedEntity::GetAllAttached()
//{
//    std::vector<GameObject*> result;
//
//    for (auto &i : m_children) {
//        std::vector<GameObject*> childObjects = i->GetAllAttached();
//        result.insert(result.end(), childObjects.begin(), childObjects.end());
//    }
//
//    result.push_back(this);
//    return result;
//}
