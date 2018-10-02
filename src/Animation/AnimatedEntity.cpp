#include <utility>

//
// Created by erick on 9/9/18.
//

#include "AnimatedEntity.h"
#include "AnimationComponent.h"

Joint* AnimatedEntity::getRootJoint() {
    return m_rootJoint;
}

glm::mat4* AnimatedEntity::getJointTransforms() {
    auto * jointMatrices = new glm::mat4[m_jointCount];
    addJointsToArray(m_rootJoint, jointMatrices);
    return jointMatrices;
}

void AnimatedEntity::addJointsToArray(Joint* headJoint, glm::mat4 * jointMatrices) {
    jointMatrices[headJoint->getMeshIndex()] = headJoint->getAnimatedTransform();
    for (Joint* childJoint : headJoint->getChildren()) {
        addJointsToArray(childJoint, jointMatrices);
    }
}

AnimatedEntity::~AnimatedEntity()
{
    for (auto &m_component : m_components) {
        delete m_component;
    }

    for (auto &i : m_children) {
        delete i;
    }
}

AnimatedEntity* AnimatedEntity::AddChild(AnimatedEntity* child)
{
    m_children.push_back(child);
    child->getTransform().SetParent(&m_transform);
    return this;
}

AnimatedEntity* AnimatedEntity::AddComponent(EntityComponent<AnimatedEntity>* component)
{
    m_components.push_back(component);
    component->SetParent(this);
    return this;
}

void AnimatedEntity::ProcessInputAll(Input* input, float delta)
{
    ProcessInput(input, delta);

    for (auto &i : m_children) {
        i->ProcessInputAll(input, delta);
    }
}

void AnimatedEntity::UpdateAll(double time, float delta)
{
    Update(time, delta);

    for (auto &i : m_children) {
        i->UpdateAll(time, delta);
    }
}

void AnimatedEntity::RenderAll(RenderingEngine* engine) const
{
    if(allow_render) {
        Render(engine);

        for (auto i : m_children) {
            i->RenderAll(engine);
        }
    }
}

void AnimatedEntity::ProcessInput(Input* input, float delta)
{
//    m_transform.Update();

    for (auto &m_component : m_components) {
        m_component->ProcessInput(input, delta);
    }
}

void AnimatedEntity::Update(double time,float delta)
{
    for (auto &m_component : m_components) {
        m_component->Update(time,delta);
    }
}

void AnimatedEntity::Render(RenderingEngine* engine) const
{
    for (auto m_component : m_components) {
        m_component->Render(engine);
    }
}

std::vector<EntityComponent<AnimatedEntity> *> &AnimatedEntity::getComponents() {
    return m_components;
}

void AnimatedEntity::setRootJoint(Joint *joint) {
    m_rootJoint = joint;
    m_rootJoint->calcInverseBindTransform(glm::mat4());
}

std::vector<Joint *> AnimatedEntity::getJoints() {
    return m_joints;
}

void AnimatedEntity::doAnimation(const Animation &animation) {
    for (EntityComponent<AnimatedEntity>* component: m_components) {
        if(component->getType() == ANIMATION_COMPONENT){
            auto * component1 = reinterpret_cast<AnimationComponent*>(component);
            component1->doAnimation(animation);
        }
    }
}

void AnimatedEntity::doAnimation(int position) {
    for (EntityComponent<AnimatedEntity>* component: m_components) {
        if(component->getType() == ANIMATION_COMPONENT){
            auto * component1 = reinterpret_cast<AnimationComponent*>(component);
            component1->doAnimation(*m_animations[position]);
        }
    }
}

void AnimatedEntity::setAnimations(std::vector<Animation *> animations) {
    m_animations = std::move(animations);
}

std::vector<Animation *> AnimatedEntity::getAnimations() {
    return m_animations;
}

Animation* AnimatedEntity::getAnimation(int position) {
    return m_animations[position];
}

void AnimatedEntity::addAnimations(std::vector<Animation *> animations) {
    m_animations.insert(m_animations.end(), animations.begin(), animations.end());
}

void AnimatedEntity::addAnimation(Animation *animation) {
    m_animations.push_back(animation);
}


//std::vector<GameObject*> AnimatedEntity::GetAllAttached()
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
