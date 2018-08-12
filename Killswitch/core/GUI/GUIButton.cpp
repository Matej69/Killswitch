#include "GUIButton.h"




GUIButton::GUIButton(string nameID, unsigned int guiWindowID, int x, int y, int w, int h, MeasurementUnit sizeMUnit, MeasurementUnit posMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow, string label, void(*clickedCallback)())
	: GUIWindow(nameID, guiWindowID, x, y, w, h, sizeMUnit, posMUnit, hasParentGUIWindow, parentGUIWindow, GUIWindowType::BUTTON)
{
	this->label = label;
	this->disabled = false;
	this->clickedCallback = (clickedCallback != nullptr) ? clickedCallback : nullptr;
}


GUIButton::~GUIButton()
{
}



void GUIButton::SpecificPreRenderingTasks()
{
	ImGui::SetNextWindowBgAlpha(0.0f);
	ImGui::GetStyle().WindowBorderSize = 0.0f;	
}

void GUIButton::SpecificRenderingTasks()
{	
	ImGui::PushItemFlag(ImGuiItemFlags_Disabled, this->disabled);
	bool isClicked = ImGui::Button(this->label.c_str(), ImVec2(this->w, this->h));
	(isClicked && !this->disabled && this->clickedCallback != nullptr) ? this->clickedCallback() : NULL ;
		
}
