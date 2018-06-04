#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "core\ShaderLoader\ShaderLoader.h"
#include "core\Sprite\Sprite.h"
#include "core\Texture\Texture.h"



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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Sprite sprite = Sprite(0.1f, 0.1f, 0.5f, 0.5f);
	Sprite sprite2 = Sprite(0.3f, 0.3f, -0.3f, -0.3f);

	string path = "res/textures/larvitar.png";
	Texture texture(path);
	texture.Bind(0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		sprite.SetPosition(sprite.x + 0.0001f, sprite.y);
		sprite.Render();
		sprite2.Render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}