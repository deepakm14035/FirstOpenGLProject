#pragma once
#include<string>
#include<unordered_map>
#include "glm/glm.hpp"
struct ShaderSourceCode {
	std::string vertexShader;
	std::string fragmentShader;
};

class Shader {
private:
	unsigned int m_rendererId;
	const std::string& m_filePath;
	std::unordered_map<std::string, int> m_uniformLocationMap;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1i(const std::string& name, int i0);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, glm::mat4 mat);
private:
	ShaderSourceCode readShaderFile(const std::string& path);
	unsigned int CompileShader(const int type, const std::string& shaderCode);
	int getUniformLocation(const std::string& name);
	unsigned int createShader(const std::string& vs, const std::string& fs);
};