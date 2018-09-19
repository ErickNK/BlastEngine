#ifndef PHYSICS_OBJECT_INCLUDED_H
#define PHYSICS_OBJECT_INCLUDED_H

#include <vector>
#include "glm/glm.hpp"
#include "../../Common/math3d.h"
#include "../Colliders/Collider.h"
#include "../../Core/Entities/Entity.h"
#include "../Forces/Force.h"
#include "../../Core/Components/EntityComponent.h"
/**
* The PhysicsObject class represents an object that can be used in a physics
* engine.
*/
class PhysicsObject: public EntityComponent<Entity>
{
public:
	/**
	* Creates a PhysicsObject in a usable state.
	*
	* @param collider A collider representing the shape and position of the
	*                   object. Should be in allocated memory.
	* @param velocity How fast this object is moving and in what direction.
	*/
    PhysicsObject(float mass, const glm::vec3& initialVelocity, Collider* collider) :
    mass(mass),
    velocity(initialVelocity),
    collider(collider) { collider->SetParent(this); }

//	PhysicsObject(const PhysicsObject& other);
//
//	void operator=(PhysicsObject other);
//
//	virtual ~PhysicsObject();

	/**
	* Calculate this object's new location and properties after delta seconds.
    *
    * If we know the current position and velocity of an object,
    * and the forces that will be applied to it,
    * we can integrate to find its position and velocity at some point in the future.
	*
	* @param delta How much time to simulate.
	*/
	virtual void Integrate(double time, float delta) {};


	/**
	* Returns a collider in the position of this object, updating the
	* collider's position if necessary.
	*/
	inline const Collider& GetCollider()
	{
//		Find distance between current and old position
		glm::vec3 translation = m_entity->getTransform().GetPos() - m_oldPosition;
//		Update old position back to current position.
		m_oldPosition = m_entity->getTransform().GetPos();
//		Move collider by distance moved.
//        collider->Transform(translation);

		return *collider;
	}

	// Getter and Setters
	inline const glm::vec3& getVelocity() const { return velocity; }
    inline void SetVelocity(const glm::vec3& v) { velocity = v; }

protected:
    /** Mass of the object */
    float mass = 1.0f;

    /** How fast this object is moving and in what direction */
    glm::vec3 velocity = glm::vec3(0,0,0);

	/** The position of the object when the collider was last updated. */
    glm::vec3 m_oldPosition = glm::vec3(0,0,0);

	/** The collider representing the shape and position of this object. */
	Collider* collider;

    /** Forces currently affecting the object */
    std::vector<Force*> forces;
};

#endif
