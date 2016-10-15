#pragma once

#ifndef _PONGGAMEWINDOW_H_
#define _PONGGAMEWINDOW_H_

// Includes
#include <Windows/AbstractSubAppWindow.hpp>

// Forward declarations
class PongGameController;

wxDECLARE_EVENT(PONG_EVT_FIELD_CHANGED, wxThreadEvent);

class PongGameWindow : public LightBulb::AbstractSubAppWindow
{
private:
	wxPanel* panel;
	wxToolBar* toolbar;
	PongGameController* getController();
protected:
	DECLARE_EVENT_TABLE();
public:
	PongGameWindow(PongGameController* controller_, LightBulb::AbstractWindow* parent = nullptr);
	void paintEvent(wxPaintEvent & evt);
	void resize(wxSizeEvent & evt);
	void paintNow();
	void refreshField(wxThreadEvent& evt);
	void toolBarClicked(wxCommandEvent& evt);
	void render(wxDC& dc);

	static std::string getLabel();
};

#endif
