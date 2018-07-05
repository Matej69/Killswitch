#pragma once
#include "..\imGUI\imgui.h"
#include "..\imGUI\imgui_impl_glfw_gl3.h"
#include <GLFW/glfw3.h>
#include "..\WindowProperties\WindowProperties.h"
#include <iostream>
#include <vector>
#include <string>
#include "..\imGUI\imgui_internal.h"
using namespace std;

enum PivotPoint {
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT
};
enum ElementAlignment {
	ROWS,
	COLS
};
enum MeasurementUnit {
	PIXELS,
	PERCENT
};


class GUIWindow
{
public:
	static vector<GUIWindow> guiWindows;
	static vector<unsigned int> guiWindowIDs;
private:
	int x, y, w, h, wPercent, hPercent;
	string name;
	MeasurementUnit mUnit;
	GLFWwindow* win;

public:
	GUIWindow(string name, int x, int y, int w, int h, MeasurementUnit mUnit, GLFWwindow* win);
	~GUIWindow();
	static void CreateWindow(string name, int x, int y, int w, int h, MeasurementUnit mUnit, GLFWwindow* win);
	static void PutAllInRenderingContainer();
	static void UpdateAllPercentSize();


private:
	void PutInRenderingContainer();
	void SetSize(int w, int h);
	void UpdatePercentSize();
};

