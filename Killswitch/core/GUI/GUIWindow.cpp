#include "GUIWindow.h"

list<GUIWindow> GUIWindow::guiWindows;
list<unsigned int> GUIWindow::guiWindowIDs;
GUIWindow* GUIWindow::CreateWindow(string name, int x, int y, int w, int h, MeasurementUnit sizeMUnit, MeasurementUnit posMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow)
{
	// ASSERT if 2 GUI windows with same ID  exist
	unsigned int newId = ImHash(name.c_str(), 0);
	for (unsigned int &id : GUIWindow::guiWindowIDs)
	{
		assert(id != newId && "ASSERT MESSAGE: 2 GUI window with same nameID exists");
	}
	GUIWindow::guiWindowIDs.push_back(newId);
	GUIWindow::guiWindows.push_back(GUIWindow(name, x, y, w, h, sizeMUnit, posMUnit, hasParentGUIWindow, parentGUIWindow));
	return &GUIWindow::guiWindows.back();
}
void GUIWindow::PutAllInRenderingContainer()
{
	for (GUIWindow &guiWin : GUIWindow::guiWindows)
	{
		guiWin.PutInRenderingContainer();
	}
}
void GUIWindow::UpdateAllPercentProperties()
{
	for (GUIWindow &guiWin : GUIWindow::guiWindows)
	{
		if (guiWin.sizeMUnit == MeasurementUnit::PERCENT)
			guiWin.UpdatePercentSize();
		if (guiWin.posMUnit == MeasurementUnit::PERCENT)
			guiWin.UpdatePercentPos();
	}
}



GUIWindow::GUIWindow(string name, int x, int y, int w, int h, MeasurementUnit sizeMUnit, MeasurementUnit posMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow)
	: x(x), y(y), sizeMUnit(sizeMUnit), posMUnit(posMUnit), name(name), hasParentGUIWindow(hasParentGUIWindow), parentGUIWindow(parentGUIWindow)
{
	SetSize(w, h);
	SetPos(x, y);
}


GUIWindow::~GUIWindow()
{
}



void GUIWindow::SetSize(int w, int h)
{
	if (this->sizeMUnit == MeasurementUnit::PERCENT)
	{
		this->wPercent = w ;
		this->hPercent = h;
		UpdatePercentSize();
	}
	else
	{
		this->w = w;
		this->h = h;
	}
}
void GUIWindow::UpdatePercentSize()
{
	if (hasParentGUIWindow == true)
	{
		this->w = parentGUIWindow->w * ((float)wPercent / 100);
		this->y = parentGUIWindow->h * ((float)hPercent / 100);
	}
	else
	{
		this->w = (float)WindowProperties::w * ((float)wPercent / 100);
		this->h = (float)WindowProperties::h * ((float)hPercent / 100);
	}
}


void GUIWindow::SetPos(int x, int y)
{
	if (this->posMUnit == MeasurementUnit::PERCENT)
	{
		this->xPercent = x;
		this->yPercent = y;
		UpdatePercentPos();
	}
	else
	{
		this->x = x;
		this->y = y;
	}
}
void GUIWindow::UpdatePercentPos()
{
	if (hasParentGUIWindow == true)
	{
		this->x = parentGUIWindow->x + (parentGUIWindow->w * ((float)xPercent / 100));
		this->y = parentGUIWindow->y + (parentGUIWindow->h * ((float)yPercent / 100));
	}
	else
	{
		this->x = (float)WindowProperties::w * ((float)xPercent / 100);
		this->y = (float)WindowProperties::h * ((float)yPercent / 100);
	}
}





void GUIWindow::PutInRenderingContainer()
{
	//ImGui::SetNextWindowBgAlpha(0.0f);
	ImGui::SetNextWindowPos(ImVec2(x, y));
	ImGui::SetNextWindowSize(ImVec2(w, h));
	ImGui::GetStyle().WindowRounding = 0.0f;
	ImGui::GetStyle().WindowBorderSize = 1.0f;
	ImGui::Begin(this->name.c_str(), NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	ImGui::Text("counter XXXXX");

	ImGui::End();
}
