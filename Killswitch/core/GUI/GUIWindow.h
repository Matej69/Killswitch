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
enum GUIWindowTitleType {
	HAS_TITLE,
	NO_TITLE
};

enum GUIWindowType {
	WINDOW,
	TEXTBOX
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
public:
	string nameID;
	unsigned int guiWindowID;
	list<GUIWindow*> childrenWidnows;
	GUIWindow* parentGUIWindow;



public:
	GUIWindow();
	GUIWindow(string name, unsigned int guiWindowID, int x, int y, int w, int h, MeasurementUnit sizeMUnit, MeasurementUnit posMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow);
	~GUIWindow();
	static GUIWindow* CreateWindow(int x, int y, int w, int h, MeasurementUnit sizeMUnit, MeasurementUnit posMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow, GUIWindowTitleType titleType, string nameID = "notitle", GUIWindowType windowType = GUIWindowType::WINDOW);
	static void PutAllInRenderingContainer();
	static void UpdateAllPercentProperties();
	static void SetWindowForDestruction(GUIWindow& window);
	static void DestroyWindowsFromDestructionList();

protected:
	void PutInRenderingContainer();
	virtual void SpecificPreRenderingTasks();
	virtual void SpecificRenderingTasks();
	void SetSize(int w, int h);
	void UpdatePercentSize();
	void SetPos(int x, int y);
	void UpdatePercentPos();
};

