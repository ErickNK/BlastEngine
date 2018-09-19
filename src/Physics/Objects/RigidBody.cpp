//
// Created by erick on 9/17/18.
//

#include "RigidBody.h"


RigidBody::RigidBody(Collider *collider, const glm::vec3 &initVelocity, float mass)  :
        PhysicsObject(mass,initVelocity,collider){
    this->m_type = RIGID_BODY_COMPONENT;
    //Add gravity
//    auto * force = new Force;
//    force->setAcceleration(glm::vec3(0,-9180,0));
//    force->computeForce(mass);
//    ApplyForce(force);
}

void RigidBody::Integrate(double time, float delta) {

    /**
     *  Semi-Implicit Euler
     *  velocity = velocity + ( force / mass ) * dt;
     *  position = position + velocity * dt;
     *
     */

    //Accelerate
    glm::vec3 total_force = glm::vec3(0,0,0);
    for (Force* force: forces){
        total_force += force->getAmount();
    }

    velocity = velocity + (total_force / mass) * delta;

    //Move
    m_entity->getTransform().GetPos() =  m_entity->getTransform().GetPos() + velocity * delta;
}

void RigidBody::ApplyForce(Force* force) {
    this->forces.push_back(force);
}

void RigidBody::ApplyForce(glm::vec3 force) {

}

void RigidBody::ApplyAcceleration(glm::vec3 acceleretion) {

}

//Derivative RigidBody::evaluate(const State& initial, double t, float dt, const Derivative & d )
//{
//    State state;
//    state.position = initial.position + d.velocity * dt;
//    state.velocity = initial.velocity + d.velocity * dt;
//
//    Derivative output;
//    output.velocity = state.velocity;
//    output.acceleration = acceleration( state, t+dt );
//    return output;
//}
//
//glm::vec3 RigidBody::acceleration(const State & state, double t )
//{
//    const float k = 15.0f;
//    const float b = 0.1f;
//    return -k * state.position - b * state.velocity;
//}
//
//void RigidBody::integrateRK4( double t, float dt )
//{
//    Derivative a,b,c,d;
//
//    a = evaluate( currentState, t, 0.0f, Derivative() );
//    b = evaluate( currentState, t, dt*0.5f, a );
//    c = evaluate( currentState, t, dt*0.5f, b );
//    d = evaluate( currentState, t, dt, c );
//
//    glm::vec3 dxdt = 1.0f / 6.0f *
//                 ( a.velocity + 2.0f * ( b.velocity + c.velocity ) + d.velocity );
//
//    glm::vec3 dvdt = 1.0f / 6.0f *
//                 ( a.acceleration + 2.0f * ( b.acceleration + c.acceleration ) + d.acceleration );
//
//    currentState.position = currentState.position + dxdt * dt;
//    currentState.velocity = currentState.velocity + dvdt * dt;
//}