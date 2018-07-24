#pragma once
#include "..\Texture\Texture.h"
#include "..\GUI\GUIWindow.h"
#include <iostream>
#include <string>
using namespace std;

class GUIImage : public GUIWindow
{
public:
	GUIImage();
	GUIImage(string nameID, unsigned int guiWindowID, int x, int y, int w, int h, MeasurementUnit sizeMUnit, MeasurementUnit posMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow, string imgSrc);
	virtual ~GUIImage();
public:
	Texture* texture;


public:
	void SpecificPreRenderingTasks() override;
	void SpecificRenderingTasks() override;
};