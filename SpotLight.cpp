//
// Created by erick on 8/25/18.
//

#include "SpotLight.h"


SpotLight::SpotLight():
    PointLight(),
    direction(glm::vec3(0.0f,-1.0f, 0.0f)),
    edge(0.0f),  procEdge(cosf(glm::radians(edge))){}

SpotLight::SpotLight(
        int id, glm::vec3 color, glm::vec3 position, glm::vec3 direction,
        GLfloat ambientIntensity, GLfloat diffuseIntensity,
        GLfloat constant, GLfloat linear, GLfloat quadratic,
        GLfloat edge
        ) :
        PointLight(
                id, color, position,
                ambientIntensity, diffuseIntensity,
                constant, linear, quadratic
                ),
        direction(glm::normalize(direction)), edge(edge), procEdge(cosf(glm::radians(edge))){}

SpotLight::~SpotLight() {}

void SpotLight::UseLight(SpotLightUniforms *spotLightUniforms) {
        glUniform3f(spotLightUniforms[id].position_u,position.x,position.y,position.z);

        glUniform3f(spotLightUniforms[id].direction_u,direction.x,position.y,position.z);

        glUniform1f(spotLightUniforms[id].edge_u,procEdge);

        glUniform1f(spotLightUniforms[id].attenuation_constant_u,constant);

        glUniform1f(spotLightUniforms[id].attenuation_linear_u,linear);

        glUniform1f(spotLightUniforms[id].attenuation_quadratic_u,quadratic);

        glUniform3f(spotLightUniforms[id].base.color_u,color.x,color.y,color.z);

        glUniform1f(spotLightUniforms[id].base.ambient_intensity_u,ambientIntensity);

        glUniform1f(spotLightUniforms[id].base.diffuse_intensity_u,diffuseIntensity);
}

void SpotLight::SetFlashLight(glm::vec3 pos, glm::vec3 dir) {
        position = pos;
        direction = dir;
}
