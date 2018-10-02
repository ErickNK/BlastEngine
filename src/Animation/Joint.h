//
// Created by erick on 9/9/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_JOINT_H
#define MORDEROPENGLUDEMYTUTORIAL_JOINT_H

#include "../Common/CommonValues.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

class Joint {
public:
    Joint() = default;

    Joint(int index, std::string& name, glm::mat4 localBindTransform);

    void addChild(Joint* child);

    const glm::mat4 &getInverseBindTransform() const;

    void setAnimatedTransform(const glm::mat4 &animatedTransform);

    const glm::mat4 &getAnimatedTransform() const;

    void calcInverseBindTransform(glm::mat4 parentModelOriginalTransform);

    void setIndex(int m_index);

    void setName(std::string m_name);

    void setOffsetMatrix(glm::mat4 m_offsetMatrix);

    void setMeshIndex(int mesh_index);

    int getMeshIndex();

    void setParent(Joint *parent);

    void setLocalOriginalTransform(glm::mat4 localOriginalTransform);

    const std::vector<Joint *> &getChildren() const;

    std::string getName();

    Joint *getParent();

//    void operator=(Joint* joint){
//        this->m_mesh_index = joint->getMeshIndex();
//        this->m_name = joint->getName();
//        this->m_children = joint->getChildren();
//    }
private:
    /**
     * Index relative to the skeleton
     * */
    int m_index;

    /**
     * Index relative to the mesh's bones
     * */
    int m_mesh_index;

    std::string m_name;

    std::vector<Joint*>  m_children;

    Joint* m_parent = nullptr;

    /**
     * Current position, rotation, scale being shown in animation.
     * This transform is in model-space and not in relation with the parent.
     * */
    glm::mat4 m_animatedTransform = glm::mat4();

    /**
     * Original inversed transform of joint in relation to the model itself when no animation is
     * applied.
     * */
    glm::mat4 m_inverseModelOriginalTransform = glm::mat4();

    /**
     * Original transform of joint in relation to its parent when no animation is applied.
     * */
    glm::mat4 m_localOriginalTransform = glm::mat4();

    /**
     * offset matrix declares the transformation needed to transform from mesh space
     * to the local space of this bone.
     * */
    glm::mat4 m_offsetMatrix = glm::mat4();
};


#endif //MORDEROPENGLUDEMYTUTORIAL_JOINT_H
