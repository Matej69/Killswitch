#pragma once
#include "..\imGUI\imgui.h"
#include "..\imGUI\imgui_impl_glfw_gl3.h"
#include <GLFW/glfw3.h>
#include "..\WindowProperties\WindowProperties.h"
#include <iostream>
#include <list>
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
	static list<GUIWindow> guiWindows;
	static list<unsigned int> guiWindowIDs;
private:
	int x, y, w, h, wPercent, hPercent, xPercent, yPercent;
	string name;
	MeasurementUnit sizeMUnit;
	MeasurementUnit posMUnit;
	bool hasParentGUIWindow;
	GUIWindow* parentGUIWindow;

public:
	GUIWindow(string name, int x, int y, int w, int h, MeasurementUnit sizeMUnit, MeasurementUnit posMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow);
	~GUIWindow();
	static GUIWindow* CreateWindow(string name, int x, int y, int w, int h, MeasurementUnit sizeMUnit, MeasurementUnit posMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow);
	static void PutAllInRenderingContainer();
	static void UpdateAllPercentProperties();

private:
	void PutInRenderingContainer();
	void SetSize(int w, int h);
	void UpdatePercentSize();
	void SetPos(int x, int y);
	void UpdatePercentPos();
};

