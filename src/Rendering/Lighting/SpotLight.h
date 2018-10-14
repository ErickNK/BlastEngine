//
// Created by erick on 8/25/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_SPOTLIGHT_H
#define MORDEROPENGLUDEMYTUTORIAL_SPOTLIGHT_H


#include "PointLight.h"
#include "../Camera/Camera.h"

class SpotLight : public PointLight {

public:
    SpotLight();

    SpotLight(
            glm::vec3 color, glm::vec3 position, glm::vec3 direction,
            GLfloat ambientIntensity, GLfloat diffuseIntensity,
            glm::vec3 attenuation,
            GLfloat edge, GLfloat shadowWidth, GLfloat shadowHeight);

    ~SpotLight() override;

	void UseLight(Shader* shader) override;

    void SetAsFlashLight(const Camera& camera);

	static void SetupUniforms(std::map<std::string, GLint>& m_uniforms, GLuint shaderProgram);

/*    void AddToEngine(CoreEngine *engine) override;*/
private:

    GLfloat edge, procEdge;

    glm::vec3 direction;

};


#endif //MORDEROPENGLUDEMYTUTORIAL_SPOTLIGHT_H
