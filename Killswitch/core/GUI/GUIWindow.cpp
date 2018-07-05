#include "GUIWindow.h"

vector<GUIWindow> GUIWindow::guiWindows;
vector<unsigned int> GUIWindow::guiWindowIDs;
void GUIWindow::CreateWindow(string name, int x, int y, int w, int h, MeasurementUnit mUnit, GLFWwindow* win)
{
	// ASSERT if 2 GUI windows with same ID  exist
	unsigned int newId = ImHash(name.c_str(), 0);
	for (unsigned int &id : GUIWindow::guiWindowIDs)
	{
		assert(id != newId && "ASSERT MESSAGE: 2 GUI window with same nameID exists");
	}
	GUIWindow::guiWindowIDs.push_back(newId);
	GUIWindow::guiWindows.push_back(GUIWindow(name, x, y, w, h, mUnit, win));
}
void GUIWindow::PutAllInRenderingContainer()
{
	for (GUIWindow &guiWin : GUIWindow::guiWindows)
	{
		guiWin.PutInRenderingContainer();
		cout << guiWin.x << " " << guiWin.y << " " << guiWin.w << " " << guiWin.h << " " << endl;
	}
}
void GUIWindow::UpdateAllPercentSize()
{
	for (GUIWindow &guiWin : GUIWindow::guiWindows)
	{
		guiWin.UpdatePercentSize();
	}
}



GUIWindow::GUIWindow(string name, int x, int y, int w, int h, MeasurementUnit mUnit, GLFWwindow* win)
	: x(x), y(y), mUnit(mUnit), win(win), name(name)
{
	SetSize(w, h);
}


GUIWindow::~GUIWindow()
{
}


void GUIWindow::UpdatePercentSize()
{
	if (this->mUnit == MeasurementUnit::PERCENT)
	{
		this->w = (float)WindowProperties::w * ((float)wPercent / 100);
		this->h = (float)WindowProperties::h * ((float)hPercent / 100);
	}
}
void GUIWindow::SetSize(int w, int h)
{
	if (this->mUnit == MeasurementUnit::PERCENT)
	{
		this->wPercent = w;
		this->hPercent = h;
		this->w = (float)WindowProperties::w * ((float)wPercent / 100);
		this->h = (float)WindowProperties::h * ((float)hPercent / 100);
	}
	else 
	{
		this->w = w;
		this->h = h;
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
	ImGui::Text("counter h ghg hjhhjhhjh hjghhjghj ghjg hjgjhgj hgjhgj");
	ImGui::End();
}
