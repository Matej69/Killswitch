#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct ShaderSources
{
	std::string vertex;
	std::string fragment;
};
static ShaderSources ParseShader(const std::string& filepath)
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

static unsigned int CompileShader(unsigned int shaderType, const std::string shaderSource)
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
		std::cout << "Failed to compile shader :" << ((shaderType== GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT") << std::endl;
		std::cout << "Message : " << msg << std::endl;
	}

	return shaderID;
}

static unsigned int CreateShader(const std::string vShaderSource, const std::string fShaderSource) 
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


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "GLEW INIT ERROR";

	float data[6] = {
		-1.0f, 0.0f,
		0.0f,	1.0f,
		1.0f,	-1.0f,
	};
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	
	ShaderSources shaderSources = ParseShader("res/shaders/basic.shader");

	std::string vs, fs;
	unsigned int shaderID = CreateShader(shaderSources.vertex, shaderSources.fragment);
	glUseProgram(shaderID);


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteProgram(shaderID);
	glfwTerminate();
	return 0;
}