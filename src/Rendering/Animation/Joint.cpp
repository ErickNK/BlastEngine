//
// Created by erick on 9/9/18.
//

#include "Joint.h"

Joint::Joint(int index, std::string& name, glm::mat4 localBindTransform) : m_index(index),
m_name(name),
m_localBindTransform(localBindTransform) {}

void Joint::addChild(Joint child) {
    m_children.push_back(child);
}

void Joint::calcInverseBindTransform(glm::mat4 parentBindTransform) {
    glm::mat4 bindTransform = parentBindTransform * m_localBindTransform;
//        Matrix4f.invert(bindTransform, inverseBindTransform);

    for (Joint child : m_children) {
        child.calcInverseBindTransform(bindTransform);
    }
}

const glm::mat4 &Joint::getInverseBindTransform() const {
    return m_inverseBindTransform;
}

void Joint::setAnimatedTransform(const glm::mat4 &animatedTransform) {
    Joint::m_animatedTransform = animatedTransform;
}

const glm::mat4 &Joint::getAnimatedTransform() const {
    return m_animatedTransform;
}
