// Includes
#include "LightBulbExamplePrec.hpp"
#include "Examples/PongEvolution/PongGameWindow.hpp"
#include "PongGameController.hpp"
#include <wx/artprov.h>
#include <Examples/TicTacToeEvolution/TicTacToeGameWindow.hpp>
#include "LightBulb/Learning/Evolution/AbstractCombiningStrategy.hpp"
#include "LightBulb/Learning/Evolution/AbstractCoevolutionFitnessFunction.hpp"

BEGIN_EVENT_TABLE(PongGameWindow, wxFrame)
EVT_PAINT(PongGameWindow::paintEvent)
EVT_SIZE(PongGameWindow::resize)
END_EVENT_TABLE()

wxDEFINE_EVENT(PONG_EVT_FIELD_CHANGED, wxThreadEvent);

enum
{
	TOOLBAR_STOP_WATCHMODE,
	TOOLBAR_START_WATCHMODE,
};

PongGameWindow::PongGameWindow(PongGameController& controller_, AbstractWindow& parent)
	:AbstractSubAppWindow(controller_, getLabel(), parent)
{
	panel = nullptr;
	Bind(PONG_EVT_FIELD_CHANGED, &PongGameWindow::refreshField, this);

	toolbar = CreateToolBar();
	toolbar->AddTool(TOOLBAR_STOP_WATCHMODE, "WatchMode Off", wxArtProvider::GetBitmap(wxART_GO_FORWARD));
	toolbar->AddTool(TOOLBAR_START_WATCHMODE, "WatchMode On", wxArtProvider::GetBitmap(wxART_DELETE));
	toolbar->Bind(wxEVT_TOOL, wxCommandEventFunction(&PongGameWindow::toolBarClicked), this);
	toolbar->Realize();

	toolbar->EnableTool(TOOLBAR_START_WATCHMODE, true);
	toolbar->EnableTool(TOOLBAR_STOP_WATCHMODE, false);

	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	panel = new wxPanel(this);
	panel->SetMinSize(wxSize(getController().getProperties().width + getController().getProperties().paddleWidth * 2, getController().getProperties().height));
	
	sizer->Add(panel, 1, wxEXPAND);
	SetSizerAndFit(sizer);
}

void PongGameWindow::paintEvent(wxPaintEvent& evt)
{
	paintNow();
}

void PongGameWindow::resize(wxSizeEvent& evt)
{
	Layout();
	paintNow();
}

void PongGameWindow::paintNow()
{
	if (panel)
	{
		wxClientDC dc(panel);
		render(dc);
	}
}

void PongGameWindow::refreshField(wxThreadEvent& evt)
{
	paintNow();
}

void PongGameWindow::toolBarClicked(wxCommandEvent& evt)
{
	if (evt.GetId() == TOOLBAR_STOP_WATCHMODE)
	{
		toolbar->EnableTool(TOOLBAR_STOP_WATCHMODE, false);
		getController().stopWatchMode();
		toolbar->EnableTool(TOOLBAR_START_WATCHMODE, true);

		paintNow();
	}
	else if (evt.GetId() == TOOLBAR_START_WATCHMODE)
	{
		toolbar->EnableTool(TOOLBAR_START_WATCHMODE, false);
		getController().startWatchMode();
		toolbar->EnableTool(TOOLBAR_STOP_WATCHMODE, true);
		wxThreadEvent tEvt;
		refreshField(tEvt);
	}
	
}

void PongGameWindow::render(wxDC& dc)
{ 
	// draw some text
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.SetBackgroundMode(wxSOLID);

	dc.Clear();

	int width, height;
	PongGameProperties& properties = getController().getProperties(); 
	PongGameState& state = getController().getState();
	panel->GetClientSize(&width, &height);

	dc.DrawRectangle(0, state.paddle2Pos, properties.paddleWidth, properties.paddleHeight);
	dc.DrawRectangle(properties.width + properties.paddleWidth, state.paddle1Pos, properties.paddleWidth, properties.paddleHeight);

	dc.DrawCircle(state.ballPosX + properties.paddleWidth + properties.ballRad / 2, state.ballPosY + properties.ballRad / 2, properties.ballRad / 2);
}

std::string PongGameWindow::getLabel()
{
	return "PongGame";
}

PongGameController& PongGameWindow::getController()
{
	return static_cast<PongGameController&>(*controller);
}
