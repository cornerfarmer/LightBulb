#pragma once

#ifndef _MOUNTAINCARWINDOW_H_
#define _MOUNTAINCARWINDOW_H_

// Includes
#include <Windows/AbstractSubAppWindow.hpp>

// Forward declarations
class MountainCarController;

wxDECLARE_EVENT(MOUNTAINCAR_EVT_POS_CHANGED, wxThreadEvent);

class MountainCarWindow : public LightBulb::AbstractSubAppWindow
{
private:
	wxPanel* panel;
	wxToolBar* toolbar;
	MountainCarController& getController();
protected:
	DECLARE_EVENT_TABLE();
public:
	MountainCarWindow(MountainCarController& controller_, AbstractWindow& parent);
	void paintEvent(wxPaintEvent& evt);
	void resize(wxSizeEvent& evt);
	void paintNow();
	void refreshField(wxThreadEvent& evt);
	void toolBarClicked(wxCommandEvent& evt);
	void render(wxDC& dc);

	static std::string getLabel();
};

#endif
