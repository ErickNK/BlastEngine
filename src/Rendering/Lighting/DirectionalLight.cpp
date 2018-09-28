#include <utility>

//
// Created by erick on 8/24/18.
//

#include "DirectionalLight.h"
#include "../../Core/CoreEngine.h"

DirectionalLight::DirectionalLight() :
    Light(DIRECTIONAL_LIGHT),
    direction(glm::vec3(0.0f,-1.0f,0.0f))
{
    m_transform.LookAt(glm::vec3(0.0f,-1.0f,0.0f));
    m_transform.SetPos(glm::vec3(0.0f,100.0f,0.0f));
    m_shadow.m_shadow_camera.setProjection(glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f));
}

DirectionalLight::DirectionalLight(
        glm::vec3 color,
        glm::vec3 direction,
        GLfloat ambientIntensity, GLfloat diffuseIntensity,
        GLfloat shadowWidth, GLfloat shadowHeight,
        glm::mat4 lightProj) :
    Light(DIRECTIONAL_LIGHT,color,ambientIntensity,diffuseIntensity,shadowWidth,shadowHeight),
    direction(glm::normalize(direction))
{

    m_transform.SetPos(glm::vec3(0.0f,40.0f,5.0f));
    m_transform.LookAt(direction);
    m_shadow.m_shadow_camera.setProjection(lightProj);


    GLenum options[NUM_FBO_OPTIONS];

    options[TYPE] = GL_TEXTURE;
    options[TEXTURE_TYPE] = GL_TEXTURE_2D;
    options[INTERNAL_COMPONENT_FORMAT] = GL_DEPTH_COMPONENT32;
    options[EXTERNAL_COMPONENT_FORMAT] = GL_DEPTH_COMPONENT;
    options[ATTACHMENT_TYPE] = GL_DEPTH_ATTACHMENT;
    options[ENABLE_OVERLAY_FILTER] = GL_TRUE;
    options[ENABLE_WRAP_FILTER] = GL_TRUE;
    options[WRAP_FILTER] = GL_CLAMP_TO_BORDER;
    options[OVERLAY_FILTER] = GL_LINEAR;
    m_shadow.shadow_map_fbo.Generate(m_shadow.shadow_map_texture, shadowWidth,shadowHeight,options);

    GLenum someError = glGetError();
    assert( someError == GL_NO_ERROR);
}

DirectionalLight::~DirectionalLight() = default;

void DirectionalLight::UseLight(std::map<std::string, GLint>& m_uniforms,int shadowTextureUnit) {

    glm::vec3 forward = m_transform.GetForward();

    m_shadow.lightSpace = m_shadow.m_shadow_camera.getProjection() * m_shadow.m_shadow_camera.getViewMatrix();

    //Start using Lights shadow map
    m_shadow.shadow_map_fbo.UseTexture(m_shadow.shadow_map_texture,shadowTextureUnit);

    //Set shadowTextureUnit
    glUniform1i(m_uniforms["directionalLight.shadowMap"], shadowTextureUnit);

    //Set Light Space
    glUniformMatrix4fv(m_uniforms["directionalLightSpace"], 1, GL_FALSE, glm::value_ptr(m_shadow.lightSpace));

    //Set Light Direction
    glUniform3f(m_uniforms["directionalLight.direction"],forward.x,forward.y,forward.z);

    //Set Light Color
    glUniform3f(m_uniforms["directionalLight.base.colour"],color.x,color.y,color.z);

    //Set Ambient Intensity
    glUniform1f(m_uniforms["directionalLight.base.ambientIntensity"],ambientIntensity);

    //Set Diffuse Intensity
    glUniform1f(m_uniforms["directionalLight.base.diffuseIntensity"],diffuseIntensity);

    //Cell shading
    glUniform1i(m_uniforms["allowCellShading"],m_allow_cell_shading);

    glUniform1i(m_uniforms["cellShadingLevels"],m_cell_shading_level);

    GLenum someError = glGetError();
    assert( someError == GL_NO_ERROR);
}

void DirectionalLight::SetupUniforms(std::map<std::string, GLint>& m_uniforms,GLuint shaderProgram) {

    m_uniforms["cellShadingLevels"] =
            glGetUniformLocation(shaderProgram, "cellShadingLevels");

    m_uniforms["allowCellShading"] =
            glGetUniformLocation(shaderProgram, "allowCellShading");

    m_uniforms["directionalLightSpace"] =
			glGetUniformLocation(shaderProgram, "directionalLightSpace");

    m_uniforms["directionalLight.shadowMap"] =
			glGetUniformLocation(shaderProgram, "directionalLight.shadowMap");

    m_uniforms["directionalLight.direction"] =
            glGetUniformLocation(shaderProgram, "directionalLight.direction");

    m_uniforms["directionalLight.base.colour"] =
            glGetUniformLocation(shaderProgram, "directionalLight.base.colour");

    m_uniforms["directionalLight.base.ambientIntensity"] =
            glGetUniformLocation(shaderProgram, "directionalLight.base.ambientIntensity");

    m_uniforms["directionalLight.base.diffuseIntensity"] =
            glGetUniformLocation(shaderProgram, "directionalLight.base.diffuseIntensity");

    GLenum someError = glGetError();
    assert( someError == GL_NO_ERROR);
}

/*void DirectionalLight::AddToEngine(CoreEngine *engine) {
    engine->GetRenderingEngine()->AddDirectionalLight(this);
}*/
