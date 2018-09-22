//
// Created by erick on 9/9/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_ANIMATEDGAMEOBJECT_H
#define MORDEROPENGLUDEMYTUTORIAL_ANIMATEDGAMEOBJECT_H


#include "Joint.h"
#include "../Common/math3d.h"
#include "../Core/Entities/MeshedEntity.h"
#include "Animation.h"

class AnimatedEntity : public MeshedEntity{
public:
    AnimatedEntity() = default;

    AnimatedEntity(Mesh &mesh, Transform &transform, Material &material, Joint& rootJoint, int jointCount) :
    MeshedEntity(mesh,transform,material) ,
    m_rootJoint(rootJoint),
    m_jointCount(jointCount){
        m_rootJoint.calcInverseBindTransform(glm::mat4());
    };

    const Joint &getRootJoint() const;

    /**
     * Gets an array of the all important model-space transforms of all the
     * joints (with the current animation pose applied) in the entity. The
     * joints are ordered in the array based on their joint index. The position
     * of each joint's transform in the array is equal to the joint's index.
     *
     * @return The array of model-space transforms of the joints in the current
     *         animation pose.
     */
    glm::mat4* getJointTransforms() {
        auto * jointMatrices = new glm::mat4[m_jointCount];
        addJointsToArray(m_rootJoint, jointMatrices);
        return jointMatrices;
    }


private:
    /**
    * This adds the current model-space transform of a joint (and all of its
    * descendants) into an array of transforms. The joint's transform is added
    * into the array at the position equal to the joint's index.
    *
    * @param headJoint
    *            - the current joint being added to the array. This method also
    *            adds the transforms of all the descendents of this joint too.
    * @param jointMatrices
    *            - the array of joint transforms that is being filled.
    */
    void addJointsToArray(Joint headJoint, glm::mat4 * jointMatrices) {
        jointMatrices[headJoint.m_index] = headJoint.getAnimatedTransform();
        for (Joint childJoint : headJoint.m_children) {
            addJointsToArray(childJoint, jointMatrices);
        }
    }

    // skeleton
    Joint m_rootJoint;
    int m_jointCount = 0;

};


#endif //MORDEROPENGLUDEMYTUTORIAL_ANIMATEDGAMEOBJECT_H
