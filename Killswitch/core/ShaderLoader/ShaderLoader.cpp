#include "ShaderLoader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct ShaderSources;

ShaderLoader::ShaderLoader()
{
}


ShaderLoader::~ShaderLoader()
{
}

ShaderSources ShaderLoader::ParseShader(const std::string& filepath)
{
	enum ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };
	ShaderType shaderType = ShaderType::NONE;
	std::string shaderSources[2];
	std::ifstream stream(filepath);
	std::string line;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				shaderType = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				shaderType = ShaderType::FRAGMENT;
			}
		}
		else
		{
			shaderSources[(int)shaderType].append(line + "\n");
		}
	}
	return { shaderSources[0], shaderSources[1] };
}

unsigned int ShaderLoader::CompileShader(unsigned int shaderType, const std::string shaderSource)
{
	unsigned int shaderID = glCreateShader(shaderType);
	const char* shaderSourceChar = shaderSource.c_str();
	glShaderSource(shaderID, 1, &shaderSourceChar, nullptr);
	glCompileShader(shaderID);

	int result;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		int length;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
		char* msg = (char*)alloca(length * sizeof(char));
		std::cout << "Failed to compile shader :" << ((shaderType == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT") << std::endl;
		std::cout << "Message : " << msg << std::endl;
	}

	return shaderID;
}

unsigned int ShaderLoader::CreateShader(const std::string vShaderSource, const std::string fShaderSource)
{
	unsigned int programID = glCreateProgram();
	unsigned int vShaderID = CompileShader(GL_VERTEX_SHADER, vShaderSource);
	unsigned int fShaderID = CompileShader(GL_FRAGMENT_SHADER, fShaderSource);
	glAttachShader(programID, vShaderID);
	glAttachShader(programID, fShaderID);
	glLinkProgram(programID);
	glValidateProgram(programID);
	glDeleteShader(vShaderID);
	glDeleteShader(fShaderID);
	return programID;
}
