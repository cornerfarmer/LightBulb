// Includes
#include "Examples/TicTacToeEvolution/TicTacToeGameWindow.hpp"

BEGIN_EVENT_TABLE(TicTacToeGameWindow, wxFrame)
EVT_PAINT(TicTacToeGameWindow::paintEvent)
END_EVENT_TABLE()

TicTacToeGameWindow::TicTacToeGameWindow(TicTacToeGameController* controller_, AbstractWindow* parent)
	:AbstractWindow(TicTacToeGameWindow::getLabel(), parent)
{
	controller = controller_;
}

void TicTacToeGameWindow::paintEvent(wxPaintEvent& evt)
{
	wxPaintDC dc(this);
	render(dc);
}

void TicTacToeGameWindow::paintNow()
{
	wxClientDC dc(this);
	render(dc);
}

void TicTacToeGameWindow::render(wxDC& dc)
{ 
	// draw some text
	dc.DrawText(wxT("Testing"), 40, 60);
}

std::string TicTacToeGameWindow::getLabel()
{
	return "TicTacToeGame";
}
