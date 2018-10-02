#include <utility>

//
// Created by erick on 9/9/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_ANIMATEDGAMEOBJECT_H
#define MORDEROPENGLUDEMYTUTORIAL_ANIMATEDGAMEOBJECT_H


#include "Joint.h"
#include "../Common/math3d.h"
#include "../Core/Entities/MeshedEntity.h"
#include "Animation.h"
#include "AnimatedMesh.h"

class AnimatedEntity : public Entity{
public:
    AnimatedEntity() = default;

    AnimatedEntity(AnimatedMesh &mesh, Transform &transform, Material &material, std::vector<Joint*>& joints) :
    m_mesh(&mesh),
    m_material(&material),
    m_joints(std::move(joints))
    {
        m_transform = transform;
    };

    virtual ~AnimatedEntity();

    void ProcessInputAll(Input* input, float delta);

    void UpdateAll(double time,float delta);

    void RenderAll(RenderingEngine* engine) const;

    AnimatedEntity* AddChild(AnimatedEntity* child);

    AnimatedEntity* AddComponent(EntityComponent<AnimatedEntity>* component);

    std::vector<EntityComponent<AnimatedEntity> *> &getComponents();

    Joint* getRootJoint();

    /**
     * Gets an array of the all important model-space transforms of all the
     * joints (with the current animation pose applied) in the entity. The
     * joints are ordered in the array based on their joint index. The position
     * of each joint's transform in the array is equal to the joint's index.
     *
     * @return The array of model-space transforms of the joints in the current
     *         animation pose.
     */
    glm::mat4* getJointTransforms();

    /**
     * Indicates that the entity should carry out the given animation. Resets
     * the animation time so that the new animation starts from the beginning.
     *
     * @param animation
     *            - the new animation to carry out.
     */
    void doAnimation(const Animation &animation);

    void doAnimation(int position);

    AnimatedMesh* getMesh() { return m_mesh; }

    void setMesh(AnimatedMesh* m_mesh) { AnimatedEntity::m_mesh = m_mesh; }

    Material* getMaterial() { return m_material; }

    void setMaterial(Material* m_material) { AnimatedEntity::m_material = m_material; }

    void setRootJoint(Joint *joint);

    std::vector<Joint *> getJoints();

    void setAnimations(std::vector<Animation*> animations);

    void addAnimations(std::vector<Animation*> animations);

    void addAnimation(Animation* animation);

    std::vector<Animation *> getAnimations();

    Animation* getAnimation(int position);

private:
    // skeleton
    Joint* m_rootJoint = nullptr;

    int m_jointCount = 0;

    std::vector<Joint*> m_joints;

    std::vector<Animation*> m_animations;

    //Skin
    AnimatedMesh* m_mesh = nullptr;

    Material* m_material = nullptr;

    std::vector<AnimatedEntity*> m_children;

    std::vector<EntityComponent<AnimatedEntity>*> m_components;

    void ProcessInput(Input* input, float delta) override;

    void Update(double time, float delta) override;

    void Render(RenderingEngine* engine) const;

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
    void addJointsToArray(Joint* headJoint, glm::mat4 * jointMatrices);

};


#endif //MORDEROPENGLUDEMYTUTORIAL_ANIMATEDGAMEOBJECT_H
