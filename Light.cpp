//
// Created by erick on 8/23/18.
//

#include "Light.h"

Light::Light():
    color(glm::vec3(1.0f,1.0f,1.0f)),
    ambientIntensity(1.0f),
    diffuseIntensity(0.0f) {}

Light::Light(glm::vec3 color,GLfloat ambientIntensity, GLfloat diffuseIntensity) :
    color(color),
    ambientIntensity(ambientIntensity),
    diffuseIntensity(diffuseIntensity){}

Light::~Light() {}
