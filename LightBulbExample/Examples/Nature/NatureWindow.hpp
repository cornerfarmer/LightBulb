#pragma once

#ifndef _NATUREWINDOW_H_
#define _NATUREWINDOW_H_

// Includes
#include <Windows/AbstractSubAppWindow.hpp>

// Forward declarations
class NatureController;

wxDECLARE_EVENT(NATURE_EVT_FIELD_CHANGED, wxThreadEvent);

class NatureWindow : public LightBulb::AbstractSubAppWindow
{
private:
	wxPanel* panel;
	wxToolBar* toolbar;
	NatureController& getController();
protected:
	DECLARE_EVENT_TABLE();
public:
	NatureWindow(NatureController& controller_, LightBulb::AbstractWindow* parent = nullptr);
	void paintEvent(wxPaintEvent& evt);
	void resize(wxSizeEvent& evt);
	void paintNow();
	void refreshField(wxThreadEvent& evt);
	void toolBarClicked(wxCommandEvent& evt);
	void render(wxDC& dc);

	static std::string getLabel();
};

#endif
