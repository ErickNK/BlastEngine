#include "Shader.h"
#include <iostream>
#include <fstream>

Shader::Shader(const std::string& fileName) {
    //Create program
    m_program = glCreateProgram();

    //Load and Create Shaders
    m_shaders[VERTEX_SHADER] = CreateShader(LoadShader(fileName + ".vs"),GL_VERTEX_SHADER);
    m_shaders[FRAGMENT_SHADER] = CreateShader(LoadShader(fileName + ".fs"),GL_FRAGMENT_SHADER);

    //Attach shaders to the program.
    for (GLuint m_shader : m_shaders)
        glAttachShader(m_program, m_shader);

    //Link program
    glLinkProgram(m_program);
    CheckShaderError(m_program,GL_LINK_STATUS,true,"Error: Program linking failed!:");

    //Validate program
    glValidateProgram(m_program);
    CheckShaderError(m_program,GL_VALIDATE_STATUS,true,"Error: Program validation failed!:");

    CreateUniforms();
}

void Shader::CreateUniforms() {
    //Setup Main Uniforms
    m_uniforms[VIEW_U] = glGetUniformLocation(m_program, "view");
    m_uniforms[MODEL_U] = glGetUniformLocation(m_program, "model");
    m_uniforms[PROJECTION_U] = glGetUniformLocation(m_program, "projection");
    m_uniforms[CAMERA_POSITION_U] = glGetUniformLocation(m_program, "cameraPosition");
    m_uniforms[CAMERA_POSITION_U] = glGetUniformLocation(m_program, "cameraDirection");

    m_uniforms[POINT_LIGHT_COUNT_U] = glGetUniformLocation(m_program, "pointLightCount");
    m_uniforms[SPOT_LIGHT_COUNT_U] = glGetUniformLocation(m_program, "spotLightCount");

    for (size_t i = 0; i < MAX_POINT_LIGHTS; i++){

        char locBuff[100] = {'\0'};

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.colour",i);
        m_point_lights[i].base.color_u = glGetUniformLocation(m_program, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.ambientIntensity",i);
        m_point_lights[i].base.ambient_intensity_u = glGetUniformLocation(m_program, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.diffuseIntensity",i);
        m_point_lights[i].base.diffuse_intensity_u = glGetUniformLocation(m_program, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].position",i);
        m_point_lights[i].position_u = glGetUniformLocation(m_program, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].attenuationConstant",i);
        m_point_lights[i].attenuation_constant_u = glGetUniformLocation(m_program, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].attenuationLinear",i);
        m_point_lights[i].attenuation_linear_u = glGetUniformLocation(m_program, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].attenuationQuadratic",i);
        m_point_lights[i].attenuation_quadratic_u = glGetUniformLocation(m_program, locBuff);
    }

    for (size_t i = 0; i < MAX_SPOT_LIGHTS; i++){

        char locBuff[100] = {'\0'};

        snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.colour",i);
        m_spot_lights[i].base.color_u = glGetUniformLocation(m_program, locBuff);

        snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.ambientIntensity",i);
        m_spot_lights[i].base.ambient_intensity_u = glGetUniformLocation(m_program, locBuff);

        snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.diffuseIntensity",i);
        m_spot_lights[i].base.diffuse_intensity_u = glGetUniformLocation(m_program, locBuff);

        snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.position",i);
        m_spot_lights[i].position_u = glGetUniformLocation(m_program, locBuff);

        snprintf(locBuff, sizeof(locBuff), "spotLights[%d].direction",i);
        m_spot_lights[i].direction_u = glGetUniformLocation(m_program, locBuff);

        snprintf(locBuff, sizeof(locBuff), "spotLights[%d].edge",i);
        m_spot_lights[i].edge_u = glGetUniformLocation(m_program, locBuff);

        snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.attenuationConstant",i);
        m_spot_lights[i].attenuation_constant_u = glGetUniformLocation(m_program, locBuff);

        snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.attenuationLinear",i);
        m_spot_lights[i].attenuation_linear_u = glGetUniformLocation(m_program, locBuff);

        snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.attenuationQuadratic",i);
        m_spot_lights[i].attenuation_quadratic_u = glGetUniformLocation(m_program, locBuff);
    }
}

Shader::~Shader() {
    //Detach shaders to the program.
    for (GLuint m_shader : m_shaders) {
        glDetachShader(m_program, m_shader);
        glDeleteShader(m_shader);
    }

    glDeleteProgram(m_program);
}

void Shader::Bind() {
    glUseProgram(m_program);
}

void Shader::UnBind() {
    glUseProgram(0);
}

void Shader::UpdateModel(const Transform& transform){
    glUniformMatrix4fv(m_uniforms[MODEL_U],1,GL_FALSE, glm::value_ptr(transform.GetModel()));
}

void Shader::UpdateProjection(const glm::mat4 &projection) {
    glUniformMatrix4fv(m_uniforms[PROJECTION_U],1,GL_FALSE, glm::value_ptr(projection));
}

void Shader::UpdateView(const Camera &camera) {
    glUniformMatrix4fv(m_uniforms[VIEW_U],1,GL_FALSE, glm::value_ptr(camera.getViewMatrix()));

    //Update position
    glUniform3f(m_uniforms[CAMERA_POSITION_U],camera.getPosition().x,camera.getPosition().y,camera.getPosition().z);
    glUniform3f(m_uniforms[CAMERA_DIRECTION_U],camera.getDirection().x,camera.getDirection().y,camera.getDirection().z);
}

std::string Shader::LoadShader(const std::string& fileName) {

    std::ifstream file;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
            output.append(line + "\n");
        }
    }
    else
    {
        std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage) {

    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), nullptr, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), nullptr, error);

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}

GLuint Shader::CreateShader(const std::string &text, GLenum shaderType) {

    GLuint shader = glCreateShader(shaderType);

    if(shader == 0)
        std::cerr << "Error: Shader creation failed!:" << std::endl;

    const GLchar* shaderSourceStrings[1];
    GLint shaderSourceStringLengths[1];

    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringLengths[0] = text.length();

    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
    glCompileShader(shader);

    CheckShaderError(shader,GL_COMPILE_STATUS,false,"Error: Shader compilation failed!:");

    return shader;
}

GLint *Shader::getUniforms() { return m_uniforms; }

GLuint *Shader::getShaders() { return m_shaders; }

GLuint Shader::getShaderProgram() { return m_program; }

void Shader::SetDirectionalLight(DirectionalLight *dLight) { dLight->UseLight(&m_directional_light); }

void Shader::SetPointLights(PointLight *pLights, unsigned int lightCount) {

    if (lightCount > MAX_POINT_LIGHTS) lightCount = MAX_POINT_LIGHTS;

    glUniform1i(m_uniforms[POINT_LIGHT_COUNT_U],lightCount);

    for(size_t i = 0; i < lightCount; i++){
        pLights[i].UseLight(m_point_lights);
    }
}

void Shader::SetSpotLights(SpotLight *sLights, unsigned int lightCount) {

    if (lightCount > MAX_SPOT_LIGHTS) lightCount = MAX_SPOT_LIGHTS;

    glUniform1i(m_uniforms[SPOT_LIGHT_COUNT_U],lightCount);

    for(size_t i = 0; i < lightCount; i++){
        sLights[i].UseLight(m_spot_lights);
    }
}

DirectionalLightUniforms *Shader::getDirectionalLightUniforms() {
    return &m_directional_light;
}

PointLightUniforms *Shader::getPointLightUniformsArray() {
    return m_point_lights;
}

MaterialUniforms *Shader::getMaterialUniforms() {
    return &m_material;
}



