#ifndef WIN_PROPERTIES_H
#define WIN_PROPERTIES_H
#pragma once
#include "..\imGUI\imgui.h"
#include "..\imGUI\imgui_impl_glfw_gl3.h"


class WindowProperties
{
public:
	static GLFWwindow* glfwWindow;
	static int x, y, w, h;

public:
	WindowProperties();
	~WindowProperties();
	static void SetSize(int w, int h);
};
#endif
