#include <utility>

#include "Shader.h"
#include <iostream>
#include <fstream>

Shader::Shader(ShaderType type) : m_type(type){};

Shader::Shader(std::map<int, std::string> shaderFiles, ShaderType type) :
m_shaderFiles(std::move(shaderFiles)),
m_type(type) {}

void Shader::Init(){
	//Create program
	m_program = glCreateProgram();

	//Load and Create Shaders
	for (auto const& x : m_shaderFiles) {
		//m_shaders[x.first] = CreateShader(LoadShader(x.second), x.first);
		glAttachShader(m_program, CreateShader(LoadShader(x.second), x.first));
	}

	//Attach shaders to the program.
	//for (GLuint m_shader : m_shaders)
		//glAttachShader(m_program, m_shader);

	//Link program
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed!:");

	//Validate program
	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program validation failed!:");

	//Uniforms
	CreateUniforms();
}

void Shader::CreateUniforms() {
    //Setup Main Uniforms
    m_uniforms["view"] = glGetUniformLocation(m_program, "view");
    m_uniforms["model"] = glGetUniformLocation(m_program, "model");
    m_uniforms["projection"] = glGetUniformLocation(m_program, "projection");
    m_uniforms["normalMatrix"] = glGetUniformLocation(m_program, "normalMatrix");
    m_uniforms["cameraPosition"] = glGetUniformLocation(m_program, "cameraPosition");
    m_uniforms["cameraDirection"] = glGetUniformLocation(m_program, "cameraDirection");
}

//TODO: figure out how to add multiple items in vector without the previous once being destroyed.
Shader::~Shader() {
    //Detach shaders to the program.
    //for (GLuint m_shader : m_shaders) {
    //    glDetachShader(m_program, m_shader);
    //    glDeleteShader(m_shader);
    //}

    //glDeleteProgram(m_program);
}

void Shader::Bind() {
    resetDrawingTextureUnits();
    resetGlobalTextureUnits();
    glUseProgram(m_program);
}

void Shader::UnBind() {
    resetDrawingTextureUnits();
    resetGlobalTextureUnits();
    glUseProgram(0);
}

void Shader::UpdateModel(const Transform& transform){
    glUniformMatrix4fv(m_uniforms["model"],1,GL_FALSE, glm::value_ptr(transform.GetModel()));
}

void Shader::UpdateProjection(const glm::mat4& projection) {
    glUniformMatrix4fv(m_uniforms["projection"],1,GL_FALSE, glm::value_ptr(projection));
}

void Shader::UpdateNormalMatrix(const glm::mat3& normalMatrix){
	glUniformMatrix3fv(m_uniforms["normalMatrix"], 1, GL_FALSE, glm::value_ptr(normalMatrix));
}

void Shader::UpdateView(const Camera& camera) {
    glUniformMatrix4fv(m_uniforms["view"],1,GL_FALSE, glm::value_ptr(camera.getViewMatrix()));

    //Update position
    glUniform3f(m_uniforms["cameraPosition"],camera.getPosition().x,camera.getPosition().y,camera.getPosition().z);
    glUniform3f(m_uniforms["cameraDirection"],camera.getDirection().x,camera.getDirection().y,camera.getDirection().z);
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

std::map<std::string, GLint>& Shader::getUniforms() { return m_uniforms; }

std::vector<GLuint> Shader::getShaders() { return m_shaders; }

GLuint Shader::getShaderProgram() { return m_program; }

ShaderType Shader::getType() {
    return m_type;
}

int Shader::getAvailableGlobalTextureUnit() {
    if (lastIssuedGlobalTextureUnit >= MAX_GLOBAL_TEXTURE_UNITS) {
        //TODO: Throw error
    }
    return ++lastIssuedGlobalTextureUnit;
}

int Shader::getAvailableDrawingTextureUnit() {
    if (lastIssuedDrawingTextureUnit >= MAX_DRAWING_TEXTURE_UNITS) {
        //TODO: Throw error
    }
    return ++lastIssuedDrawingTextureUnit;
}

void Shader::resetGlobalTextureUnits() {
    lastIssuedGlobalTextureUnit = -1;
}

void Shader::resetDrawingTextureUnits() {
    lastIssuedDrawingTextureUnit = MAX_DRAWING_TEXTURE_UNITS + 0;
}

