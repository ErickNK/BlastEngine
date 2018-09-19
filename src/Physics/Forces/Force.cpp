//
// Created by erick on 9/17/18.
//

#include "Force.h"

glm::vec3 Force::getAmount() const {
    return amount;
}

void Force::setAmount(glm::vec3 amount) {
    Force::amount = amount;
}


const glm::vec3 &Force::getAcceleration() const {
    return acceleration;
}

void Force::setAcceleration(const glm::vec3 &acceleration) {
    Force::acceleration = acceleration;
}

void Force::reset() {
    amount * 0.0f;
    acceleration * 0.0f;
}
