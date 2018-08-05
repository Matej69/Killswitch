#ifndef _GUIINPUT
#define _GUIINPUT

#pragma once
#include <typeinfo>
#include "..\GUI\GUIWindow.h"
#include <iostream>
#include <string>
using namespace std;

class GUIWindow;

enum InputType {
	STRING,
	INT,
	FLOAT,
	DOUBLE
};

template<class VALUE_TYPE>
class GUIInput : public GUIWindow
{
public:
	GUIInput();
	GUIInput(string nameID, unsigned int guiWindowID, int x, int y, int w, int h, MeasurementUnit sizeMUnit, MeasurementUnit posMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow, string label, VALUE_TYPE value, int maxLength);
	virtual ~GUIInput();
public:
	VALUE_TYPE value;
	InputType inputType;
	string label;
	int maxLength;
	void(*valueChangeCallback)(VALUE_TYPE);

public:
	void SpecificPreRenderingTasks() override;
	void SpecificRenderingTasks() override;

};

#endif

