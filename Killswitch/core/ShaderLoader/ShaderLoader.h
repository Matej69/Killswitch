#pragma once

#include <iostream>
#include <fstream>
#include <string>

/**
* ShaderSources holds value for vertex and fragment shader source
*/
struct ShaderSources
{
	std::string vertex;
	std::string fragment;
};


class ShaderLoader
{

public:
	ShaderLoader();
	~ShaderLoader();

	/*
	* Takes filepath of vertex and fragment shader and returns them as separated sources
	*/
	static ShaderSources ParseShader(const std::string& filepath);

	/*
	* Takes type of shader and that shaders source, creates shader ID and compiles shader, then returns ID of that compiled shader
	*/
	static unsigned int CompileShader(unsigned int shaderType, const std::string shaderSource);

	/*
	* Creates program, compiles vertex and fragment shader, attaches and links shaders to that program, returns created program ID
	*/
	static unsigned int CreateShader(const std::string vShaderSource, const std::string fShaderSource);

};

