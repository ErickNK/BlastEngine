//
// Created by erick on 9/17/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_RIGIDBODY_H
#define MORDEROPENGLUDEMYTUTORIAL_RIGIDBODY_H

#include "glm/glm.hpp"
#include "../../Core/Entities/MeshedEntity.h"
#include "../Colliders/Collider.h"
#include "../Forces/Force.h"
#include "PhysicsObject.h"
//
//struct State
//{
//    //Primary
//    /** Will carry the position of the object*/
//    glm::vec3 position;
//    /**
//     *  dp/dt = F
//     *  v = p/m
//     *  dx/dt = v
//     *
//     *  Force * delta = momentum
//     *  momentum / mass = velocity
//     *  Velocity * delta = position
//     */
//    glm::vec3 momentum;
//
//    //Secondary
//    /** How fast this object is moving and in what direction */
//    glm::vec3 velocity;
//
//    // constants
//    float mass = 1.0f; //In kilograms
//    float inverseMass;
//
//    void recalculate()
//    {
//        velocity = momentum * inverseMass;
//    }
//
//};
//
//struct Derivative
//{
//    /** How fast this object is moving and in what direction */
//    glm::vec3 velocity;
//    glm::vec3 acceleration;
//
//    /** Forces currently affecting the object */
//    std::vector<Force> forces;
//};

/**
 * A body that cannot be mutilated
 *  */
class RigidBody: public PhysicsObject {
public:
    /**
	* Creates a RigidBody in a usable state.
	*
	* @param collider A collider representing the shape and position of the
	*                   object used for collusions. Should be in allocated memory.
	* @param velocity How fast this object is moving and in what direction.
	*/
    RigidBody(Collider* collider, const glm::vec3& initVelocity, float mass);

    /**
	* Calculate this object's new location and properties after delta seconds.
    *
    * If we know the current position and velocity of an object,
    * and the forces that will be applied to it,
    * we can integrate to find its position and velocity at some point in the future.
	*
	* @param delta How much time to simulate.
	*/
    void Integrate(double time, float delta) override;

//    Derivative evaluate(const State& initial, double t, float dt, const Derivative & d ) ;
//    glm::vec3  acceleration(const State & state,double t );
//    void integrateRK4(double t, float dt );

    /**
     * Apply a force.
     * */
    void ApplyForce(Force* force);
    void ApplyForce(glm::vec3 force);
    void ApplyAcceleration(glm::vec3 acceleretion);
private:

//    State currentState;
//    Derivative currentDerivative;




};


#endif //MORDEROPENGLUDEMYTUTORIAL_RIGIDBODY_H
