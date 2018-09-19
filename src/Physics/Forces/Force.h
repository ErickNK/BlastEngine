//
// Created by erick on 9/17/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_FORCE_H
#define MORDEROPENGLUDEMYTUTORIAL_FORCE_H

#include <glm/glm.hpp>
/**
 * Force equals mass * acceleration. F = ma. a = F/m
 * Acceleration is the rate of change of velocity over time.  dv/dt = a = F/m
 * Velocity is the rate of change in position over time. dx/dt = v
 *
 *
 * */
class Force {

public:
    glm::vec3 getAmount() const;

    void setAmount(glm::vec3 amount);

    const glm::vec3 &getAcceleration() const;

    void setAcceleration(const glm::vec3 &acceleration);

    void computeForce(float mass){
        amount = acceleration * mass;
    }

    void computeAcceleration(float mass){
        acceleration = amount / mass;
    }

    void reset();

private:
    /**
     * Amount of force to apply and in what direction
     * */
    glm::vec3 amount = glm::vec3(0,0,0); //In newtons

    /**
     * Amount of acceleration and in what direction
     * */
    glm::vec3 acceleration = glm::vec3(0, 0, 0);
};


#endif //MORDEROPENGLUDEMYTUTORIAL_FORCE_H
