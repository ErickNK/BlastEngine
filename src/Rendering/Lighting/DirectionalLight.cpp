#include <utility>

//
// Created by erick on 8/24/18.
//

#include "DirectionalLight.h"
#include "../../Core/CoreEngine.h"

DirectionalLight::DirectionalLight() :
    LightEntity(DIRECTIONAL_LIGHT),
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
    LightEntity(DIRECTIONAL_LIGHT,color,ambientIntensity,diffuseIntensity,shadowWidth,shadowHeight),
    direction(glm::normalize(direction))
{

    m_transform.SetPos(glm::vec3(0.0f,40.0f,5.0f));
    m_transform.LookAt(direction);
    m_shadow.m_shadow_camera.setProjection(lightProj);


    GLenum options[NUM_FBO_OPTIONS];

    options[TYPE] = GL_TEXTURE;
    options[TEXTURE_TYPE] = GL_TEXTURE_2D;
    options[INTERNAL_COMPONENT_FORMAT] = GL_RG32F;
    options[EXTERNAL_COMPONENT_FORMAT] = GL_RGBA;
    options[DATA_VALUE_FORMAT] = GL_FLOAT;
    options[ATTACHMENT_TYPE] = GL_COLOR_ATTACHMENT0;
    options[ENABLE_OVERLAY_FILTER] = GL_TRUE;
    options[ENABLE_WRAP_FILTER] = GL_TRUE;
    options[WRAP_FILTER] = GL_CLAMP_TO_BORDER;
    options[OVERLAY_FILTER] = GL_LINEAR;
    m_shadow.shadow_map_fbo.Generate(m_shadow.shadow_map_texture, shadowWidth,shadowHeight,options);

    GLenum someError = glGetError();
    assert( someError == GL_NO_ERROR);
}

DirectionalLight::~DirectionalLight() = default;

void DirectionalLight::UseLight(Shader* shader) {
    //Get lights direction
    glm::vec3 forward = m_transform.GetForward();

    //Get light space
    m_shadow.lightSpace = m_shadow.biasMatrix //Convert to 0-1 range. Which is what depth range is
                          * m_shadow.m_shadow_camera.getProjection()
                          * m_shadow.m_shadow_camera.getViewMatrix();

    //Start using Lights shadow map
    auto shadowTextureUnit = static_cast<GLuint>(shader->getAvailableGlobalTextureUnit());
    m_shadow.shadow_map_fbo.UseTexture(m_shadow.shadow_map_texture,shadowTextureUnit);

    char locBuff[100] = {'\0'};

    //Set shadowTextureUnit
    snprintf(locBuff, sizeof(locBuff), "directionalLight[%d].shadowMap",m_id);
    shader->Uniform1i(locBuff, shadowTextureUnit);

    //Set Light Space
    snprintf(locBuff, sizeof(locBuff), "directionalLightSpace[%d]",m_id);
    shader->UniformMatrix4fv(locBuff, m_shadow.lightSpace);

    //Set Light Direction
    snprintf(locBuff, sizeof(locBuff), "directionalLight[%d].direction",m_id);
    shader->Uniform3f(locBuff,forward.x,forward.y,forward.z);

    //Set Light Color
    snprintf(locBuff, sizeof(locBuff), "directionalLight[%d].base.colour",m_id);
    shader->Uniform3f(locBuff,color.x,color.y,color.z);

    //Set Ambient Intensity
    snprintf(locBuff, sizeof(locBuff), "directionalLight[%d].base.ambientIntensity",m_id);
    shader->Uniform1f(locBuff,ambientIntensity);

    //Set Diffuse Intensity
    snprintf(locBuff, sizeof(locBuff), "directionalLight[%d].base.diffuseIntensity",m_id);
    shader->Uniform1f(locBuff,diffuseIntensity);

    //Enable/Disable cell shading
    snprintf(locBuff, sizeof(locBuff), "directionalLight[%d].base.allowCellShading",m_id);
    shader->Uniform1i(locBuff,m_allow_cell_shading);

    //Cell shading levels
    snprintf(locBuff, sizeof(locBuff), "directionalLight[%d].base.cellShadingLevels",m_id);
    shader->Uniform1i(locBuff,m_cell_shading_level);

    GLenum someError = glGetError();
    assert( someError == GL_NO_ERROR);
}

void DirectionalLight::SetupUniforms(std::map<std::string, GLint>& m_uniforms,GLuint shaderProgram) {

    m_uniforms["directionalLightCount"] = glGetUniformLocation(shaderProgram, "directionalLightCount");

    for(int i = 0; i < MAX_DIRECTIONAL_LIGHTS; i++){
        char locBuff[100] = {'\0'};

        snprintf(locBuff, sizeof(locBuff), "directionalLight[%d].base.cellShadingLevels",i);
        m_uniforms[locBuff] = glGetUniformLocation(shaderProgram, locBuff);

        snprintf(locBuff, sizeof(locBuff), "directionalLight[%d].base.allowCellShading",i);
        m_uniforms[locBuff] = glGetUniformLocation(shaderProgram, locBuff);

        snprintf(locBuff, sizeof(locBuff), "directionalLightSpace[%d]",i);
        m_uniforms[locBuff] = glGetUniformLocation(shaderProgram, locBuff);

        snprintf(locBuff, sizeof(locBuff), "directionalLight[%d].shadowMap",i);
        m_uniforms[locBuff] = glGetUniformLocation(shaderProgram, locBuff);

        snprintf(locBuff, sizeof(locBuff), "directionalLight[%d].direction",i);
        m_uniforms[locBuff] = glGetUniformLocation(shaderProgram, locBuff);

        snprintf(locBuff, sizeof(locBuff), "directionalLight[%d].base.colour",i);
        m_uniforms[locBuff] = glGetUniformLocation(shaderProgram, locBuff);

        snprintf(locBuff, sizeof(locBuff), "directionalLight[%d].base.ambientIntensity",i);
        m_uniforms[locBuff] = glGetUniformLocation(shaderProgram, locBuff);

        snprintf(locBuff, sizeof(locBuff), "directionalLight[%d].base.diffuseIntensity",i);
        m_uniforms[locBuff] = glGetUniformLocation(shaderProgram, locBuff);

    }

    GLenum someError = glGetError();
    assert( someError == GL_NO_ERROR);
}
