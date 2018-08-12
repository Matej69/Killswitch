#ifndef _GUIWINDOW
#define _GUIWINDOW

#pragma once
#include <GL/glew.h>
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
enum GUIWindowNameIDType {
	HAS_NAME_ID,
	NO_NAME_ID
};

enum GUIWindowType {
	WINDOW,
	BUTTON,
	TEXTBOX,
	INPUT,
	IMAGE,
};


class GUIWindow
{
public:
	static list<GUIWindow*> guiWindows;
	static list<GUIWindow*> guiWindowsForDestroy;
	static unsigned int lastGUITitleID;
protected:
	int x, y, w, h, wPercent, hPercent, xPercent, yPercent;
	MeasurementUnit sizeMUnit;
	MeasurementUnit posMUnit;
	bool hasParentGUIWindow;
	GUIWindowType windowType;
public:
	string nameID;
	unsigned int guiWindowID;
	list<GUIWindow*> childrenWidnows;
	GUIWindow* parentGUIWindow;



public:
	GUIWindow();
	GUIWindow(string name, unsigned int guiWindowID, int x, int y, int w, int h, MeasurementUnit sizeMUnit, MeasurementUnit posMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow, GUIWindowType windowType);
	~GUIWindow();
	static GUIWindow* CreateWindow(int x, int y, int w, int h, MeasurementUnit posMUnit, MeasurementUnit sizeMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow, GUIWindowNameIDType nameIDType, string nameID = "notitle");
	static GUIWindow* CreateButton(int x, int y, int w, int h, MeasurementUnit posMUnit, MeasurementUnit sizeMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow, GUIWindowNameIDType nameIDType, string label, void(*clickedCallback)(), string nameID = "notitle");
	static GUIWindow* CreateTextbox(int x, int y, int w, int h, MeasurementUnit posMUnit, MeasurementUnit sizeMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow, GUIWindowNameIDType nameIDType, string textboxText, string nameID = "notitle");
	static GUIWindow* CreateImage(int x, int y, int w, int h, MeasurementUnit posMUnit, MeasurementUnit sizeMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow, GUIWindowNameIDType nameIDType, string imgSrc, string nameID = "notitle");
	static GUIWindow* CreateInput(int x, int y, int w, int h, MeasurementUnit posMUnit, MeasurementUnit sizeMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow, GUIWindowNameIDType nameIDType, string label, int value, void(*valueChangeCallback)(int), int maxValue = INT_MAX, int minValue = INT_MIN, string nameID = "notitle");
	static GUIWindow* CreateInput(int x, int y, int w, int h, MeasurementUnit posMUnit, MeasurementUnit sizeMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow, GUIWindowNameIDType nameIDType, string label, float value, void(*valueChangeCallback)(float), int maxValue = INT_MAX, int minValue = INT_MIN, string nameID = "notitle");
	static GUIWindow* CreateInput(int x, int y, int w, int h, MeasurementUnit posMUnit, MeasurementUnit sizeMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow, GUIWindowNameIDType nameIDType, string label, double value, void(*valueChangeCallback)(double), int maxValue = INT_MAX, int minValue = INT_MIN, string nameID = "notitle");
	static GUIWindow* CreateInput(int x, int y, int w, int h, MeasurementUnit posMUnit, MeasurementUnit sizeMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow, GUIWindowNameIDType nameIDType, string label, string value, void(*valueChangeCallback)(string), int maxLength = 50, int minLength = 0, string nameID = "notitle");
	static unsigned int SetNameIDAndGenerateHash(string& nameID, GUIWindowNameIDType nameIDType);
	static void PrepareAllForRendering();
	static void UpdateAllPercentProperties();
	static void SetWindowForDestruction(GUIWindow& window);
	static void DestroyWindowsFromDestructionList();

protected:
	void PrepareForRendering();
	virtual void SpecificPreRenderingTasks();
	virtual void SpecificRenderingTasks();
	void SetSize(int w, int h);
	void UpdatePercentSize();
	void SetPos(int x, int y);
	void UpdatePercentPos();
};

#endif

