#include "GUITextbox.h"



GUITextbox::GUITextbox()
{
}

GUITextbox::~GUITextbox()
{
}



GUITextbox::GUITextbox(string nameID, unsigned int guiWindowID, int x, int y, int w, int h, MeasurementUnit sizeMUnit, MeasurementUnit posMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow)
	: GUIWindow(nameID, guiWindowID, x, y, w, h, sizeMUnit, posMUnit, hasParentGUIWindow, parentGUIWindow)
{
}


void GUITextbox::SpecificPreRenderingTasks()
{
	//ImGui::SetNextWindowBgAlpha(0.0f);
}

void GUITextbox::SpecificRenderingTasks()
{
	cout << "VIRTUAL OVERRIDEN" << endl;
	ImGui::TextWrapped(this->text.c_str());
}

