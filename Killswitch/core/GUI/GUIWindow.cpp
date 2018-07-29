#include "GUIWindow.h"
#include "GUITextbox.h"
#include "GUIImage.h"
#include "GUIInput.h"

GUIWindow::GUIWindow(string nameID, unsigned int guiWindowID, int x, int y, int w, int h, MeasurementUnit sizeMUnit, MeasurementUnit posMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow, GUIWindowType windowType)
	: x(x), y(y), sizeMUnit(sizeMUnit), posMUnit(posMUnit), nameID(nameID), hasParentGUIWindow(hasParentGUIWindow), parentGUIWindow(parentGUIWindow), guiWindowID(guiWindowID), windowType(windowType)
{
	SetSize(w, h);
	SetPos(x, y);
}

GUIWindow::GUIWindow()
{
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

void GUIWindow::PrepareForRendering()
{
	//ImGui::SetNextWindowBgAlpha(0.0f);
	ImGui::SetNextWindowPos(ImVec2(x, y));
	ImGui::SetNextWindowSize(ImVec2(w, h));
	this->SpecificPreRenderingTasks();
	ImGui::Begin(this->nameID.c_str(), NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
	this->SpecificRenderingTasks();
	ImGui::End();
}

void GUIWindow::SpecificPreRenderingTasks()
{
	ImGui::GetStyle().WindowRounding = 0.0f;
	ImGui::GetStyle().WindowBorderSize = 1.0f;
	ImGui::SetNextWindowBgAlpha(1.0f);
}
void GUIWindow::SpecificRenderingTasks()
{
}










/* ####################################################################################################################################
 * ######################################################### STATIC FUNCTIONS #########################################################
 * ####################################################################################################################################
 */


list<GUIWindow*> GUIWindow::guiWindows;
list<GUIWindow*> GUIWindow::guiWindowsForDestroy;
unsigned int GUIWindow::lastGUITitleID = 0;


GUIWindow* GUIWindow::CreateWindow(int x, int y, int w, int h, MeasurementUnit sizeMUnit, MeasurementUnit posMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow, GUIWindowNameIDType nameIDType, string nameID)
{
	unsigned int newHashedId = GUIWindow::SetNameIDAndGenerateHash(nameID, nameIDType);
	GUIWindow::guiWindows.push_back(new GUIWindow(nameID, newHashedId, x, y, w, h, sizeMUnit, posMUnit, hasParentGUIWindow, parentGUIWindow, GUIWindowType::WINDOW));
	//if (parentGUIWindow != nullptr)
	//	parentGUIWindow->childrenWidnows.push_back(&GUIWindow::guiWindows.back());
	return GUIWindow::guiWindows.back();
}

GUIWindow* GUIWindow::CreateTextbox(int x, int y, int w, int h, MeasurementUnit sizeMUnit, MeasurementUnit posMUnit, bool hasParentGUIWindow, GUIWindow * parentGUIWindow, GUIWindowNameIDType nameIDType, string textboxText, string nameID)
{
	unsigned int newHashedId = GUIWindow::SetNameIDAndGenerateHash(nameID, nameIDType);
	GUIWindow::guiWindows.push_back(new GUITextbox(nameID, newHashedId, x, y, w, h, sizeMUnit, posMUnit, hasParentGUIWindow, parentGUIWindow, textboxText));
	return GUIWindow::guiWindows.back();
}

GUIWindow* GUIWindow::CreateImage(int x, int y, int w, int h, MeasurementUnit sizeMUnit, MeasurementUnit posMUnit, bool hasParentGUIWindow, GUIWindow * parentGUIWindow, GUIWindowNameIDType nameIDType, string imgSrc, string nameID)
{
	unsigned int newHashedId = GUIWindow::SetNameIDAndGenerateHash(nameID, nameIDType);
	GUIWindow::guiWindows.push_back(new GUIImage(nameID, newHashedId, x, y, w, h, sizeMUnit, posMUnit, hasParentGUIWindow, parentGUIWindow, imgSrc));
	return GUIWindow::guiWindows.back();
}


GUIWindow* GUIWindow::CreateInput(int x, int y, int w, int h, MeasurementUnit sizeMUnit, MeasurementUnit posMUnit, bool hasParentGUIWindow, GUIWindow * parentGUIWindow, GUIWindowNameIDType nameIDType, string label, int value, int maxLength, string nameID)
{
	unsigned int newHashedId = GUIWindow::SetNameIDAndGenerateHash(nameID, nameIDType);
	GUIWindow::guiWindows.push_back(new GUIInput<int>(nameID, newHashedId, x, y, w, h, sizeMUnit, posMUnit, hasParentGUIWindow, parentGUIWindow, label, value, maxLength));
	return GUIWindow::guiWindows.back();
}
GUIWindow* GUIWindow::CreateInput(int x, int y, int w, int h, MeasurementUnit sizeMUnit, MeasurementUnit posMUnit, bool hasParentGUIWindow, GUIWindow * parentGUIWindow, GUIWindowNameIDType nameIDType, string label, float value, int maxLength, string nameID)
{
	unsigned int newHashedId = GUIWindow::SetNameIDAndGenerateHash(nameID, nameIDType);
	GUIWindow::guiWindows.push_back(new GUIInput<float>(nameID, newHashedId, x, y, w, h, sizeMUnit, posMUnit, hasParentGUIWindow, parentGUIWindow, label, value, maxLength));
	return GUIWindow::guiWindows.back();
}
GUIWindow* GUIWindow::CreateInput(int x, int y, int w, int h, MeasurementUnit sizeMUnit, MeasurementUnit posMUnit, bool hasParentGUIWindow, GUIWindow * parentGUIWindow, GUIWindowNameIDType nameIDType, string label, double value, int maxLength, string nameID)
{
	unsigned int newHashedId = GUIWindow::SetNameIDAndGenerateHash(nameID, nameIDType);
	GUIWindow::guiWindows.push_back(new GUIInput<double>(nameID, newHashedId, x, y, w, h, sizeMUnit, posMUnit, hasParentGUIWindow, parentGUIWindow, label, value, maxLength));
	return GUIWindow::guiWindows.back();
}
GUIWindow* GUIWindow::CreateInput(int x, int y, int w, int h, MeasurementUnit sizeMUnit, MeasurementUnit posMUnit, bool hasParentGUIWindow, GUIWindow * parentGUIWindow, GUIWindowNameIDType nameIDType, string label, string value, int maxLength, string nameID)
{
	unsigned int newHashedId = GUIWindow::SetNameIDAndGenerateHash(nameID, nameIDType);
	GUIWindow::guiWindows.push_back(new GUIInput<string>(nameID, newHashedId, x, y, w, h, sizeMUnit, posMUnit, hasParentGUIWindow, parentGUIWindow, label, value, maxLength));
	return GUIWindow::guiWindows.back();
}


unsigned int GUIWindow::SetNameIDAndGenerateHash(string& nameID, GUIWindowNameIDType nameIDType)
{
	unsigned int newHashedId;
	// ASSERT if 2 GUI windows with same ID  exist
	if (nameIDType == GUIWindowNameIDType::HAS_NAME_ID)
	{
		newHashedId = ImHash(nameID.c_str(), 0);
	}
	else if (nameIDType == GUIWindowNameIDType::NO_NAME_ID)
	{
		nameID = to_string(++lastGUITitleID);
		newHashedId = ImHash(to_string(lastGUITitleID).c_str(), 0);
	}

	for (GUIWindow* win : GUIWindow::guiWindows)
	{
		assert(win->guiWindowID != newHashedId && "ASSERT MESSAGE: 2 GUI window with same nameID exists");
	}
	return newHashedId;
}

void GUIWindow::SetWindowForDestruction(GUIWindow &window)
{
	cout << "## SETTING GUI WINDOWS IN DESTRUCTION CONTAINER:" << endl;
	for (GUIWindow* win : GUIWindow::guiWindows)
	{
		if ((win == &window || (win->parentGUIWindow != nullptr && win->parentGUIWindow == &window)))
		{
			cout << "nameID=" << win->nameID << "\t type=" << win->windowType << endl;
			GUIWindow::guiWindowsForDestroy.push_back(win);
		}
	}
	cout << "## DONE SETTING GUI WINDOWS IN DESTRUCTION CONTAINER" << endl;
}

void GUIWindow::DestroyWindowsFromDestructionList()
{
	cout << "** DESTROYING GUI WINDOWS FROM DESTRUCTION CONTAINER:" << endl;
	for (GUIWindow* winToDestroy : GUIWindow::guiWindowsForDestroy)
	{
		GUIWindow::guiWindows.remove_if([&winToDestroy](GUIWindow* win)
		{
			if (winToDestroy->guiWindowID == win->guiWindowID)
				cout << "nameID=" << win->nameID << "\t type=" << win->windowType << endl;
			return (winToDestroy->guiWindowID == win->guiWindowID);
		});
	}
	cout << "** DESTROYING GUI WINDOWS FROM DESTRUCTION CONTAINER" << endl;
}

void GUIWindow::PrepareAllForRendering()
{
	for (GUIWindow* guiWin : GUIWindow::guiWindows)
	{
		guiWin->PrepareForRendering();
	}
}

void GUIWindow::UpdateAllPercentProperties()
{
	for (GUIWindow* guiWin : GUIWindow::guiWindows)
	{
		if (guiWin->sizeMUnit == MeasurementUnit::PERCENT)
			guiWin->UpdatePercentSize();
		if (guiWin->posMUnit == MeasurementUnit::PERCENT)
			guiWin->UpdatePercentPos();
	}
}
