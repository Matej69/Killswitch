#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "core\ShaderLoader\ShaderLoader.h"
#include "core\Sprite\Sprite.h"
#include "core\Texture\Texture.h"
#include "core\GameClock\GameClock.h"
#include "core\imGUI\imgui.h"
#include "core\imGUI\imgui_impl_glfw_gl3.h"


using namespace std;
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

	// Setup ImGui
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Sprite sprite = Sprite(0.1f, 0.1f, 0.5f, 0.5f, "res/textures/larvitar.png");
	Sprite sprite2 = Sprite(2.0f, 2.0f, 0.0f, 0.0f, "res/textures/larvitar.png");


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		GameClock::OnFrameStart();
		// imGUI stuf called at atart of every frame
		ImGui_ImplGlfwGL3_NewFrame();

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		sprite.SetPosition(sprite.x + 0.0001f, sprite.y);
		sprite.Render();
		sprite2.Render();





		// imGUI rendering
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
		// game end frame calculation
		GameClock::OnFrameEnd();
		cout << GameClock::fps << endl;
		cout << GameClock::deltaTime << endl;
	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}