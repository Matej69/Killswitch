#include "WindowProperties.h"

GLFWwindow* WindowProperties::glfwWindow = nullptr;
int WindowProperties::w = 0;
int WindowProperties::h = 0;


WindowProperties::WindowProperties()
{
}


WindowProperties::~WindowProperties()
{
}


void WindowProperties::SetSize(int w, int h)
{
	WindowProperties::w = w;
	WindowProperties::h = h;
}