#pragma once
#include "..\GUI\GUIWindow.h"
#include <iostream>
#include <string>
using namespace std;

class GUITextbox : public GUIWindow
{
public:
	GUITextbox();
	GUITextbox(string nameID, unsigned int guiWindowID, int x, int y, int w, int h, MeasurementUnit sizeMUnit, MeasurementUnit posMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow);
	virtual ~GUITextbox();
public:
	string text;


public:
	void SpecificPreRenderingTasks() override;
	void SpecificRenderingTasks() override;
};


