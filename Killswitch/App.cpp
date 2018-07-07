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
#include "core\GUI\GUIWindow.h"
#include "core\WindowProperties\WindowProperties.h"

using namespace std;



void window_size_callback(GLFWwindow* window, int w, int h)
{
	WindowProperties::SetSize(w, h);
	GUIWindow::UpdateAllPercentProperties();
}


int main(void)
{
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;


	/* Create a windowed mode window and its OpenGL context */
	WindowProperties::SetSize(640, 480);
	window = glfwCreateWindow(WindowProperties::w, WindowProperties::h, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwSetWindowSizeCallback(window, window_size_callback);

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


	GUIWindow::CreateWindow("11", 20, 20, 50, 50, MeasurementUnit::PERCENT, MeasurementUnit::PERCENT, window);
	GUIWindow::CreateWindow("2", 0, 200, 100, 50, MeasurementUnit::PERCENT, MeasurementUnit::PIXELS, window);


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

		
		GUIWindow::PutAllInRenderingContainer();


		// imGUI rendering
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
		// game end frame calculation
		GameClock::OnFrameEnd();
		//cout << GameClock::fps << endl;
		//cout << GameClock::deltaTime << endl;
	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}