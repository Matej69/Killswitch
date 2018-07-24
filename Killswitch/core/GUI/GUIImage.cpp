#include "GUIImage.h"


GUIImage::GUIImage()
{
}

GUIImage::~GUIImage()
{
}



GUIImage::GUIImage(string nameID, unsigned int guiWindowID, int x, int y, int w, int h, MeasurementUnit sizeMUnit, MeasurementUnit posMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow, string imgSrc)
	: GUIWindow(nameID, guiWindowID, x, y, w, h, sizeMUnit, posMUnit, hasParentGUIWindow, parentGUIWindow, GUIWindowType::IMAGE)
{
	texture = new Texture(imgSrc);
}


void GUIImage::SpecificPreRenderingTasks()
{
	ImGui::SetNextWindowBgAlpha(0.0f);
	ImGui::GetStyle().WindowBorderSize = 0.0f;
}

void GUIImage::SpecificRenderingTasks()
{
	ImGui::Image((void*)(intptr_t)this->texture->textureID, ImVec2(this->w, this->h), ImVec2(0, 1), ImVec2(1, 0));
}
