#include "Shader.h"
#include <GLEW/glew.h>
#include <fstream>
#include <sstream>
#include "renderer.h"
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


ShaderSourceCode Shader::readShaderFile(const std::string& path) {
    std::ifstream stream(path);

    enum class ShaderType {
        NONE = -1, Vertex = 0, Fragment = 1
    };

    std::string line;
    std::stringstream str[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::Vertex;
            }
            else {
                type = ShaderType::Fragment;
            }
        }
        else {
            str[(int)type] << line << "\n";
        }
    }
    return { str[0].str(),str[1].str() };
}

unsigned int Shader::createShader(const std::string& vs, const std::string& fs) {
    unsigned int program = glCreateProgram();
    unsigned int vsShaderId = CompileShader(GL_VERTEX_SHADER, vs);
    unsigned int fsShaderId = CompileShader(GL_FRAGMENT_SHADER, fs);
    glAttachShader(program, vsShaderId);
    glAttachShader(program, fsShaderId);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vsShaderId);
    glDeleteShader(fsShaderId);
    return program;
}

unsigned int Shader::CompileShader(const int type, const std::string& shaderCode) {
    unsigned int id = glCreateShader(type);
    const char* src = &shaderCode[0];
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);
    int status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "error in compiling " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader. error-" << message << std::endl;
        return 0;
    }
    return id;

}


Shader::Shader(const std::string& filepath):m_filePath(filepath)
{
    ShaderSourceCode ssc = readShaderFile(filepath);
    std::cout << ssc.vertexShader << std::endl;
    m_rendererId = createShader(ssc.vertexShader, ssc.fragmentShader);

}

Shader::~Shader()
{
    GLCALL(glDeleteProgram(m_rendererId));
}

void Shader::Bind() const
{
    GLCALL(glUseProgram(m_rendererId));
}

void Shader::Unbind() const
{
    GLCALL(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int i0)
{
    GLCALL(glUniform1i(getUniformLocation(name), i0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCALL(glUniform4f(getUniformLocation(name),v0,v1,v2,v3));
}

void Shader::SetUniformMat4f(const std::string& name, glm::mat4 mat)
{
    GLCALL(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}

int Shader::getUniformLocation(const std::string& name)
{
    if (m_uniformLocationMap.find(name) != m_uniformLocationMap.end()) {
        return m_uniformLocationMap[name];
    }
    GLCALL(int location=glGetUniformLocation(m_rendererId, name.c_str()));
    if (location == -1)
        std::cout << "warning: uniform '" << name << "' does not exist" << std::endl;
    m_uniformLocationMap[name] = location;
    std::cout << "warning: uniform '" << name << "' does not exist" << std::endl;
    return location;
}
