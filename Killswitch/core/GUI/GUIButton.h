#pragma once
#include "..\GUI\GUIWindow.h"
#include <iostream>
#include <string>
using namespace std;

class GUIButton : public GUIWindow
{
private:
	string label;
	bool disabled;
public:
	void(*clickedCallback)();

public:
	GUIButton();
	GUIButton(string nameID, unsigned int guiWindowID, int x, int y, int w, int h, MeasurementUnit sizeMUnit, MeasurementUnit posMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow, string label, void(*clickedCallback)() );
	~GUIButton();

public:
	void SpecificPreRenderingTasks() override;
	void SpecificRenderingTasks() override;
};

