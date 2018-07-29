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
#include "core\GUI\GUITextbox.h"
#include "core\GUI\GUIImage.h"
#include "core\GUI\GUIInput.h"
#include "core\WindowProperties\WindowProperties.h"

using namespace std;



void window_size_callback(GLFWwindow* window, int w, int h)
{
	WindowProperties::SetSize(w, h);
	GUIWindow::UpdateAllPercentProperties();
}


int main(void)
{
	/* Initialize the library */
	if (!glfwInit())
		return -1;


	/* Create a windowed mode window and its OpenGL context */
	WindowProperties::SetSize(900, 550);
	WindowProperties::glfwWindow = glfwCreateWindow(WindowProperties::w, WindowProperties::h, "Hello World", NULL, NULL);
	if (!WindowProperties::glfwWindow)
	{
		glfwTerminate();
		return -1;
	}
	glfwSetWindowSizeCallback(WindowProperties::glfwWindow, window_size_callback);

	/* Make the window's context current */
	glfwMakeContextCurrent(WindowProperties::glfwWindow);

	if (glewInit() != GLEW_OK)
		std::cout << "GLEW INIT ERROR";

	// Setup ImGui
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(WindowProperties::glfwWindow, true);
	ImGui::StyleColorsDark();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Sprite sprite = Sprite(0.1f, 0.1f, 0.5f, 0.5f, "res/textures/larvitar.png");
	Sprite sprite2 = Sprite(2.0f, 2.0f, 0.0f, 0.0f, "res/textures/larvitar.png");


	GUIWindow* p = GUIWindow::CreateWindow(0, 0, 100, 20, MeasurementUnit::PERCENT, MeasurementUnit::PERCENT, false, NULL, GUIWindowNameIDType::HAS_NAME_ID, "yolo");
	for (int i = 0; i < 5; ++i)
		GUIWindow::CreateWindow(i * 16, 2, 15, 15, MeasurementUnit::PERCENT, MeasurementUnit::PERCENT, true, p, GUIWindowNameIDType::NO_NAME_ID);
	GUIWindow::CreateTextbox(0, 80, 100, 20, MeasurementUnit::PERCENT, MeasurementUnit::PERCENT, false, p, GUIWindowNameIDType::NO_NAME_ID, "neki jakooooo sexy text koji tu stoji burazzcccccccccccc ccccccccccccccccccccccccccccccccc cccccccccccccc sssssssssssssssssssssssssssssssssss ssssssss eeeeeeeeeeeee ffffffffffffffffff vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv v v vvvvvvvv zz jakooooo sexy text koji tu stoji burazzcccccccccccc ccccccccccccccccccccccccccccccccc cccccccccccccc sssssssssssssssssssssssssssssssssss ssssssss eeeeeeeeeeeee ffffffffffffffffff vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv v v vvvvvvvv zz jakooooo sexy text koji tu stoji burazzcccccccccccc ccccccccccccccccccccccccccccccccc cccccccccccccc sssssssssssssssssss", "12345");
	GUIWindow::CreateImage(0, 0, 50, 50, MeasurementUnit::PERCENT, MeasurementUnit::PERCENT, false, p, GUIWindowNameIDType::NO_NAME_ID, "res/textures/larvitar.png", "12345");


	GUIWindow::CreateInput(0, 0, 50, 50, MeasurementUnit::PERCENT, MeasurementUnit::PIXELS, false, NULL, GUIWindowNameIDType::NO_NAME_ID, "mylabel", "tst", 10);
	GUIWindow::CreateInput(100, 100, 50, 50, MeasurementUnit::PERCENT, MeasurementUnit::PIXELS, false, NULL, GUIWindowNameIDType::NO_NAME_ID, "mylabel1", 123, 10);
	GUIWindow::CreateInput(200, 200, 50, 50, MeasurementUnit::PERCENT, MeasurementUnit::PIXELS, false, NULL, GUIWindowNameIDType::NO_NAME_ID, "mylabel2", 123.0f, 10);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(WindowProperties::glfwWindow))
	{
		GameClock::OnFrameStart();
		// imGUI stuf called at start of every frame
		ImGui_ImplGlfwGL3_NewFrame();

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		sprite.SetPosition(sprite.x + 0.0001f, sprite.y);
		sprite.Render();
		sprite2.Render();

		// imGUI rendering
		GUIWindow::PrepareAllForRendering();
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		/* Swap front and back buffers */
		glfwSwapBuffers(WindowProperties::glfwWindow);
		/* Poll for and process events */
		glfwPollEvents();
		// game end frame calculation
		GameClock::OnFrameEnd();
		// cout << GameClock::fps << endl;
		// cout << GameClock::deltaTime << endl;
	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}