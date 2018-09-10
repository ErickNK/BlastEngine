//
// Created by erick on 9/9/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_JOINT_H
#define MORDEROPENGLUDEMYTUTORIAL_JOINT_H

#include "../../Common/CommonValues.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

class Joint {
public:
    Joint(int index, std::string& name, glm::mat4 localBindTransform);

    void addChild(Joint child);
    const glm::mat4 &getInverseBindTransform() const;
    void setAnimatedTransform(const glm::mat4 &animatedTransform);
    const glm::mat4 &getAnimatedTransform() const;
    void calcInverseBindTransform(glm::mat4 parentBindTransform);

    int m_index;// ID
    std::string m_name;
    std::vector<Joint>  m_children;
private:
    glm::mat4 m_animatedTransform = glm::mat4();
    glm::mat4 m_inverseBindTransform = glm::mat4();
    const glm::mat4 m_localBindTransform;

};


#endif //MORDEROPENGLUDEMYTUTORIAL_JOINT_H
