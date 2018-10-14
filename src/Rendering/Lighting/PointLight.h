//
// Created by erick on 8/24/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_POINTLIGHT_H
#define MORDEROPENGLUDEMYTUTORIAL_POINTLIGHT_H

#include <map>
#include "../../Common/CommonValues.h"
#include "../../Core/Entities/LightEntity.h"

class PointLight : public LightEntity {

public:
    PointLight();

    PointLight(glm::vec3 color, glm::vec3 position,
            GLfloat ambientIntensity, GLfloat diffuseIntensity,
            glm::vec3 attenuation,
			GLfloat shadowWidth, GLfloat shadowHeight);

    ~PointLight() override;

    void CalculateRange();

	void UseLight(Shader* shader) override;

	static void SetupUniforms(std::map<std::string, GLint>& m_uniforms, GLuint shaderProgram);

    /*void AddToEngine(CoreEngine *engine) override;*/
protected:

    glm::vec3 m_attenuation;

    float m_range;

    const int COLOR_DEPTH = 256;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_POINTLIGHT_H
