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

    //Setup Uniforms
    m_uniforms[VIEW_U] = glGetUniformLocation(m_program, "view");
    m_uniforms[MODEL_U] = glGetUniformLocation(m_program, "model");
    m_uniforms[PROJECTION_U] = glGetUniformLocation(m_program, "projection");
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
}

std::string Shader::LoadShader(const std::string& fileName)
{
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

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
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





