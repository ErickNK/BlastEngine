#include <utility>

//
// Created by erick on 9/9/18.
//

#include "Joint.h"

Joint::Joint(int index, std::string& name, glm::mat4 localBindTransform) :
m_index(index),
m_name(name),
m_localOriginalTransform(localBindTransform) {}

void Joint::addChild(Joint* child) {
    child->setParent(this);
    m_children.push_back(child);
}

void Joint::calcInverseBindTransform(glm::mat4 parentModelOriginalTransform) {
    glm::mat4 modelOriginalTransform = parentModelOriginalTransform * m_localOriginalTransform;
    m_inverseModelOriginalTransform = glm::inverse(modelOriginalTransform);

    for (Joint* child : m_children) {
        child->calcInverseBindTransform(modelOriginalTransform);
    }
}

const glm::mat4 &Joint::getInverseBindTransform() const {
    return m_inverseModelOriginalTransform;
}

void Joint::setAnimatedTransform(const glm::mat4 &animatedTransform) {
    Joint::m_animatedTransform = animatedTransform;
}

const glm::mat4 &Joint::getAnimatedTransform() const {
    return m_animatedTransform;
}

void Joint::setIndex(int m_index) {
    Joint::m_index = m_index;
}

void Joint::setName(std::string m_name) {
    Joint::m_name = std::move(m_name);
}

void Joint::setOffsetMatrix(glm::mat4 m_offsetMatrix) {
    Joint::m_offsetMatrix = m_offsetMatrix;
}

void Joint::setParent(Joint *parent) {
    m_parent = parent;
}

void Joint::setMeshIndex(int mesh_index) {
    Joint::m_mesh_index = mesh_index;
}

int Joint::getMeshIndex() {
    return m_mesh_index;
}

void Joint::setLocalOriginalTransform(glm::mat4 localOriginalTransform) {
    m_localOriginalTransform = localOriginalTransform;
}

const std::vector<Joint *> &Joint::getChildren() const {
    return m_children;
}

std::string Joint::getName() {
    return m_name;
}

Joint *Joint::getParent() {
    return m_parent;
}
