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
	ImGui::GetIO().IniFilename = NULL;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Sprite sprite = Sprite(0.1f, 0.1f, 0.5f, 0.5f, "res/textures/larvitar.png");
	Sprite sprite2 = Sprite(2.0f, 2.0f, 0.0f, 0.0f, "res/textures/larvitar.png");

	GUITextbox* p =  (GUITextbox*)GUIWindow::CreateTextbox(0, 0, 100, 0, MeasurementUnit::PERCENT, MeasurementUnit::PERCENT, false, NULL, GUIWindowNameIDType::NO_NAME_ID, "sadasdas das d");
	
	GUIWindow::CreateImage(25, 25, 60, 40, MeasurementUnit::PERCENT, MeasurementUnit::PERCENT, false, NULL, GUIWindowNameIDType::NO_NAME_ID, "res/textures/illidan.png");
	GUIWindow::CreateButton(10, 55, 300, 100, MeasurementUnit::PERCENT, MeasurementUnit::PIXELS, false, NULL, GUIWindowNameIDType::NO_NAME_ID, "yolo boy", []() { cout << "yoloooooooo"; });
	GUIWindow::CreateInput(0, 0, 100, 0, MeasurementUnit::PERCENT, MeasurementUnit::PERCENT, false, NULL, GUIWindowNameIDType::NO_NAME_ID, "mylabeeel", "tst", [](string s) { cout << s << endl; }, 10);
	GUIWindow::CreateInput(0, 35, 20, 0, MeasurementUnit::PERCENT, MeasurementUnit::PERCENT, false, NULL, GUIWindowNameIDType::NO_NAME_ID, "mylabeeel", 12334.0, [](double d) { cout << d << endl; }, 5);
	string s = "Neki super text Neki super textNeki super textNeki super text Neki super text Neki super text Neki super text Neki super textNeki super textNeki super text Neki super text Neki super textNeki super text Neki super textNeki super textNeki super text Neki super text Neki super textNeki super text Neki super textNeki super textNeki super text Neki super text Neki super textNeki super text Neki super textNeki super textNeki super text Neki super text Neki super textNeki super text Neki super textNeki super textNeki super text Neki super text Neki super textNeki super text Neki super textNeki super textNeki super text Neki super text Neki super textNeki super text Neki super textNeki super textNeki super text Neki super text Neki super textNeki super text Neki super textNeki super textNeki super text Neki super text Neki super textNeki super text Neki super textNeki super textNeki super text Neki super text Neki super textNeki super text Neki super textNeki super textNeki super text Neki super text Neki super textNeki super text Neki super textNeki super textNeki super text Neki super text Neki super textNeki super text Neki super textNeki super textNeki super text Neki super text Neki super textNeki super text Neki super textNeki super textNeki super text Neki super text Neki super textNeki super text Neki super textNeki super textNeki super text Neki super text Neki super textNeki super text Neki super textNeki super textNeki super text Neki super text Neki super text";
	GUIWindow::CreateTextbox(10, 70, 80, 40, MeasurementUnit::PERCENT, MeasurementUnit::PERCENT, false, NULL, GUIWindowNameIDType::NO_NAME_ID, s);
	

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(WindowProperties::glfwWindow))
	{
		GameClock::OnFrameStart();
		// imGUI stuf called at start of every frame
		ImGui_ImplGlfwGL3_NewFrame();

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//sprite.SetPosition(sprite.x + 0.0001f, sprite.y);
		//sprite.Render();
		//sprite2.Render();

		p->text = to_string(GameClock::fps);

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