#pragma once

#ifndef _TICTACTOEGAMEWINDOW_H_
#define _TICTACTOEGAMEWINDOW_H_

// Includes
#include <Windows/AbstractWindow.hpp>

// Forward declarations

class TicTacToeGameController;

class TicTacToeGameWindow : public AbstractWindow
{
private:
protected:
	TicTacToeGameController* controller;
	DECLARE_EVENT_TABLE();
public:
	TicTacToeGameWindow(TicTacToeGameController* controller_, AbstractWindow* parent = NULL);
	void paintEvent(wxPaintEvent & evt);
	void paintNow();

	void render(wxDC& dc);

	static std::string getLabel();
};

#endif
