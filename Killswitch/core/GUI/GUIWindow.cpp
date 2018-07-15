#include "GUIWindow.h"


GUIWindow::GUIWindow(string nameID, unsigned int guiWindowID, int x, int y, int w, int h, MeasurementUnit sizeMUnit, MeasurementUnit posMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow)
	: x(x), y(y), sizeMUnit(sizeMUnit), posMUnit(posMUnit), nameID(nameID), hasParentGUIWindow(hasParentGUIWindow), parentGUIWindow(parentGUIWindow), guiWindowID(guiWindowID)
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
	ImGui::Begin(this->nameID.c_str(), NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoInputs);
	ImGui::Text(this->nameID.c_str());

	ImGui::End();
}










/* ####################################################################################################################################
 * ######################################################### STATIC FUNCTIONS #########################################################
 * ####################################################################################################################################
 */


list<GUIWindow> GUIWindow::guiWindows;
list<GUIWindow*> GUIWindow::guiWindowsForDestroy;
unsigned int GUIWindow::lastGUITitleID = 0;


GUIWindow* GUIWindow::CreateWindow(int x, int y, int w, int h, MeasurementUnit sizeMUnit, MeasurementUnit posMUnit, bool hasParentGUIWindow, GUIWindow* parentGUIWindow, GUIWindowTitleType titleType, string nameID)
{
	unsigned int newHashedId;
	// ASSERT if 2 GUI windows with same ID  exist
	if (titleType == GUIWindowTitleType::HAS_TITLE)
	{
		newHashedId = ImHash(nameID.c_str(), 0);
	}
	else if (titleType == GUIWindowTitleType::NO_TITLE)
	{
		nameID = to_string(++lastGUITitleID);
		newHashedId = ImHash(to_string(lastGUITitleID).c_str(), 0);
	}

	for (GUIWindow& win : GUIWindow::guiWindows)
	{
		assert(win.guiWindowID != newHashedId && "ASSERT MESSAGE: 2 GUI window with same nameID exists");
	}

	GUIWindow::guiWindows.push_back(GUIWindow(nameID, newHashedId, x, y, w, h, sizeMUnit, posMUnit, hasParentGUIWindow, parentGUIWindow));
	//if (parentGUIWindow != nullptr)
	//	parentGUIWindow->childrenWidnows.push_back(&GUIWindow::guiWindows.back());
	return &GUIWindow::guiWindows.back();
}

void GUIWindow::SetWindowForDestruction(GUIWindow &window)
{
	cout << "PREPARING FOR DELETING WindowGUI:" << endl;
	for (GUIWindow& win : GUIWindow::guiWindows)
	{
		if ((&win == &window || (win.parentGUIWindow != nullptr && win.parentGUIWindow == &window)))
		{
			cout << "\t" + win.nameID << endl;
			GUIWindow::guiWindowsForDestroy.push_back(&win);
		}
	}	
	/*
	GUIWindow::guiWindows.remove_if([&window](GUIWindow& win)
	{
		cout << "\t" + win.nameID << endl;
		return (&win == &window || (win.parentGUIWindow != nullptr && win.parentGUIWindow == &window));
	});
	*/
	cout << "DONE PREPARING FOR DELETING " << endl;
}

void GUIWindow::DestroyWindowsFromDestructionList()
{
	cout << "DESTROYING WINDOWS:" << endl;
	for (GUIWindow* winToDestroy : GUIWindow::guiWindowsForDestroy)
	{
		GUIWindow::guiWindows.remove_if([&winToDestroy](GUIWindow& win)
		{
			cout << ((winToDestroy->guiWindowID == win.guiWindowID) ? win.nameID : "") << endl;
			return (winToDestroy->guiWindowID == win.guiWindowID);
		});
	}
	cout << "DONE DESTROYING WINDOWS" << endl;
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
