//
// Created by erick on 9/9/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_ANIMATEDGAMEOBJECT_H
#define MORDEROPENGLUDEMYTUTORIAL_ANIMATEDGAMEOBJECT_H


#include "Joint.h"
#include "../../Common/math3d.h"

class AnimatedGameObject : GameObject{
public:
    AnimatedGameObject(Mesh &mesh, Transform &transform, Material &material, Joint& rootJoint, int jointCount) :
    GameObject(mesh,transform,material) ,
    m_rootJoint(rootJoint),
    m_jointCount(jointCount){
        m_rootJoint.calcInverseBindTransform(glm::mat4());
    };

    /**
     * Instructs this entity to carry out a given animation. To do this it
     * basically sets the chosen animation as the current animation in the
     * {@link Animator} object.
     *
     * @param animation
     *            - the animation to be carried out.
     */
//    void doAnimation(Animation animation) {
//        animator.doAnimation(animation);
//    }

    const Joint &getRootJoint() const;

    /**
	 * Instructs this entity to carry out a given animation. To do this it
	 * basically sets the chosen animation as the current animation in the
	 * {@link Animator} object.
	 *
	 * @param animation
	 *            - the animation to be carried out.
	 */
    void doAnimation();

    /**
     * Updates the animator for this entity, basically updating the animated
     * pose of the entity. Must be called every frame.
     */
    void update() {
        animator.update();
    }

    /**
     * Gets an array of the all important model-space transforms of all the
     * joints (with the current animation pose applied) in the entity. The
     * joints are ordered in the array based on their joint index. The position
     * of each joint's transform in the array is equal to the joint's index.
     *
     * @return The array of model-space transforms of the joints in the current
     *         animation pose.
     */
    Matrix4f[] getJointTransforms() {
            Matrix4f[] jointMatrices = new Matrix4f[m_jointCount];
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
    void addJointsToArray(Joint headJoint, Matrix4f * jointMatrices) {
        jointMatrices[headJoint.m_index] = headJoint.getAnimatedTransform();
        for (Joint childJoint : headJoint.m_children) {
            addJointsToArray(childJoint, jointMatrices);
        }
    }

    // skeleton
    Joint m_rootJoint;
    int m_jointCount;

//private final Animator animator;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_ANIMATEDGAMEOBJECT_H
