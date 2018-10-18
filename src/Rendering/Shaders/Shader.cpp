#include <utility>

#include "Shader.h"
#include "../../Common/Util.h"
#include "../../Common/CommonValues.h"
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

    GLenum someError = glGetError();
    assert( someError == GL_NO_ERROR);
}

void Shader::CreateUniforms() {
    //Setup Main Uniforms
    m_uniforms["view"] = glGetUniformLocation(m_program, "view");
    m_uniforms["model"] = glGetUniformLocation(m_program, "model");
    m_uniforms["projection"] = glGetUniformLocation(m_program, "projection");
    m_uniforms["normalMatrix"] = glGetUniformLocation(m_program, "normalMatrix");
    m_uniforms["cameraPosition"] = glGetUniformLocation(m_program, "cameraPosition");
    m_uniforms["cameraDirection"] = glGetUniformLocation(m_program, "cameraDirection");
    m_uniforms["isAnimated"] = glGetUniformLocation(m_program, "isAnimated");

    for(int i = 0; i < MAX_CLIP_PLANES; i++){
        char locBuff[100] = {'\0'};
        snprintf(locBuff, sizeof(locBuff), "clipPlanes[%d]",i);
        m_uniforms[locBuff] = glGetUniformLocation(m_program, locBuff);
        if(m_uniforms[locBuff] != -1) {
            glUseProgram(m_program);
                glUniform4f(m_uniforms[locBuff], 0.0f, -1.0f, 0.0f, 10000000.0f);
            glUseProgram(0);
        }
    }

    for(int i = 0; i < MAX_JOINTS_PER_MESH; i++){
        char locBuff[100] = {'\0'};
        snprintf(locBuff, sizeof(locBuff), "jointTransforms[%d]",i);
        m_uniforms[locBuff] = glGetUniformLocation(m_program, locBuff);
    }
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

void Shader::UpdateView(const glm::mat4& view){
    glUniformMatrix4fv(m_uniforms["view"],1,GL_FALSE, glm::value_ptr(view));
}

void Shader::ActivateClipPlane(int id, const glm::vec4& plane){
    char locBuff[100] = {'\0'};
    snprintf(locBuff, sizeof(locBuff), "clipPlanes[%d]",id);

    if(m_uniforms.find(locBuff) != m_uniforms.end() && m_uniforms[locBuff] != -1){
        glEnable(GL_CLIP_DISTANCE0 + id);
        glUniform4f(m_uniforms[locBuff],plane.x,plane.y,plane.z,plane.w);
    }else{
        glDisable(GL_CLIP_DISTANCE0 + id);
    }

    GLenum someError = glGetError();
    assert( someError == GL_NO_ERROR);
}

void Shader::DeactivateClipPlane(int id){
    char locBuff[100] = {'\0'};
    snprintf(locBuff, sizeof(locBuff), "clipPlanes[%d]",id);

    if(m_uniforms.find(locBuff) != m_uniforms.end() && m_uniforms[locBuff] != -1){
        glDisable(GL_CLIP_DISTANCE0 + id);
        glUniform4f(m_uniforms[locBuff],0.0f,-1.0f,0.0f,100000000.0f);
    }

    GLenum someError = glGetError();
    assert( someError == GL_NO_ERROR);
}

void Shader::Uniform1i(std::string name, int value){
    if(m_uniforms.find(name) != m_uniforms.end() &&  m_uniforms[name] != -1)
        glUniform1i(m_uniforms[name],value);
}

void Shader::Uniform2f(const char *string, float d, float d1) {
    if(m_uniforms.find(string) != m_uniforms.end() && m_uniforms[string] != -1)
        glUniform2f(m_uniforms[string],d,d1);
}

void Shader::Uniform1f(const char *string, GLfloat d) {
    if(m_uniforms.find(string) != m_uniforms.end() && m_uniforms[string] != -1)
        glUniform1f(m_uniforms[string],d);
}

void Shader::Uniform3f(const char* string, GLfloat i, GLfloat i1, GLfloat i2) {
    if(m_uniforms.find(string) != m_uniforms.end() && m_uniforms[string] != -1)
        glUniform3f(m_uniforms[string],i,i1,i2);
}

void Shader::Uniform4f(const char* string, GLfloat i, GLfloat i1, GLfloat i2, GLfloat i3) {
    if(m_uniforms.find(string) != m_uniforms.end() && m_uniforms[string] != -1)
        glUniform4f(m_uniforms[string],i,i1,i2,i3);
}

void Shader::UniformMatrix4fv(const char* string, const glm::mat4& matrix) {
    if(m_uniforms.find(string) != m_uniforms.end() && m_uniforms[string] != -1)
        glUniformMatrix4fv(m_uniforms[string],1,GL_FALSE, glm::value_ptr(matrix));
}

void Shader::UpdateCamera(const Camera &camera) {
    glUniformMatrix4fv(m_uniforms["view"],1,GL_FALSE, glm::value_ptr(camera.getViewMatrix()));
    glUniformMatrix4fv(m_uniforms["projection"],1,GL_FALSE, glm::value_ptr(camera.getProjection()));

    //Update position
    glUniform3f(m_uniforms["cameraPosition"],camera.getTransform().GetPos().x,camera.getTransform().GetPos().y,camera.getTransform().GetPos().z);
    glUniform3f(m_uniforms["cameraDirection"],camera.getDirection().x,camera.getDirection().y,camera.getDirection().z);
}

std::string Shader::LoadShader(const std::string& fileName) {

    std::ifstream file;
    file.open((SHADER_DIRECTORY + fileName).c_str());

    std::string output;
    std::string line;

    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
            if(line.find("#include") == std::string::npos)
                output.append(line + "\n");
            else
            {
                std::string includeFileName = Util::Split(line, ' ')[1];
                includeFileName = includeFileName.substr(1,includeFileName.length() - 2);

                std::string toAppend = LoadShader(includeFileName);
                output.append(toAppend + "\n");
            }
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


