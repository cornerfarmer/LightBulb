#pragma once

#ifndef _TICTACTOEGAMEWINDOW_H_
#define _TICTACTOEGAMEWINDOW_H_

// Includes
#include "LightBulbApp/Windows/AbstractSubAppWindow.hpp"

// Forward declarations

class TicTacToeGameController;

wxDECLARE_EVENT(TTT_EVT_FIELD_CHANGED, wxThreadEvent);

class TicTacToeGameWindow : public LightBulb::AbstractSubAppWindow
{
private:
	LightBulb::Matrix<int> currentFields;
	wxPanel* panel;
	wxToolBar* toolbar;
	TicTacToeGameController& getController();
protected:
	DECLARE_EVENT_TABLE();
public:
	TicTacToeGameWindow(TicTacToeGameController& controller_, AbstractWindow& parent);
	void paintEvent(wxPaintEvent& evt);
	void resize(wxSizeEvent& evt);
	void paintNow();
	void refreshField(wxThreadEvent& evt);
	void toolBarClicked(wxCommandEvent& evt);
	void render(wxDC& dc);

	static std::string getLabel();
};

#endif
