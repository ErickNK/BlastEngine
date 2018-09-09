//
// Created by erick on 8/23/18.
//

#include "Light.h"

Light::Light():
    GameComponent(),
    color(glm::vec3(1.0f,1.0f,1.0f)),
    ambientIntensity(1.0f),
    diffuseIntensity(0.0f) {}

Light::Light(glm::vec3 color,GLfloat ambientIntensity, GLfloat diffuseIntensity, 
	GLfloat shadowWidth, GLfloat shadowHeight) :
    GameComponent(),
    color(color),
    ambientIntensity(ambientIntensity),
    diffuseIntensity(diffuseIntensity){

	shadowMap = new ShadowMap();
	shadowMap->Init(shadowWidth,shadowHeight);
}

Light::~Light() {}

const glm::vec3 &Light::getColor() const {
    return color;
}

GLfloat Light::getAmbientIntensity() const {
    return ambientIntensity;
}
