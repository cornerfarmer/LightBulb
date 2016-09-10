// Includes
#include "Examples/MountainCar/MountainCarWindow.hpp"
#include "MountainCarController.hpp"
#include <wx/artprov.h>
#include <Examples/TicTacToeEvolution/TicTacToeGameWindow.hpp>

BEGIN_EVENT_TABLE(MountainCarWindow, wxFrame)
EVT_PAINT(MountainCarWindow::paintEvent)
EVT_SIZE(MountainCarWindow::resize)
END_EVENT_TABLE()

wxDEFINE_EVENT(MOUNTAINCAR_EVT_POS_CHANGED, wxThreadEvent);

enum
{
	TOOLBAR_STOP_WATCHMODE,
	TOOLBAR_START_WATCHMODE,
};

using namespace LightBulb;

MountainCarWindow::MountainCarWindow(MountainCarController* controller_, AbstractWindow* parent)
	:AbstractSubAppWindow(controller_, MountainCarWindow::getLabel(), parent)
{
	panel = NULL;
	Bind(MOUNTAINCAR_EVT_POS_CHANGED, &MountainCarWindow::refreshField, this);

	toolbar = CreateToolBar();
	toolbar->AddTool(TOOLBAR_STOP_WATCHMODE, "WatchMode Off", wxArtProvider::GetBitmap(wxART_GO_FORWARD));
	toolbar->AddTool(TOOLBAR_START_WATCHMODE, "WatchMode On", wxArtProvider::GetBitmap(wxART_DELETE));
	toolbar->Bind(wxEVT_TOOL, wxCommandEventFunction(&MountainCarWindow::toolBarClicked), this);
	toolbar->Realize();

	toolbar->EnableTool(TOOLBAR_START_WATCHMODE, true);
	toolbar->EnableTool(TOOLBAR_STOP_WATCHMODE, false);

	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	panel = new wxPanel(this);
	panel->SetMinSize(wxSize(400, 400));
	
	sizer->Add(panel, 1, wxEXPAND);
	SetSizerAndFit(sizer);
}

void MountainCarWindow::paintEvent(wxPaintEvent& evt)
{
	paintNow();
}

void MountainCarWindow::resize(wxSizeEvent& evt)
{
	Layout();
	paintNow();
}

void MountainCarWindow::paintNow()
{
	if (panel)
	{
		wxClientDC dc(panel);
		render(dc);
	}
}

void MountainCarWindow::refreshField(wxThreadEvent& evt)
{
	paintNow();
}

void MountainCarWindow::toolBarClicked(wxCommandEvent& evt)
{
	if (evt.GetId() == TOOLBAR_STOP_WATCHMODE)
	{
		toolbar->EnableTool(TOOLBAR_STOP_WATCHMODE, false);
		getController()->stopWatchMode();
		toolbar->EnableTool(TOOLBAR_START_WATCHMODE, true);

		paintNow();
	}
	else if (evt.GetId() == TOOLBAR_START_WATCHMODE)
	{
		toolbar->EnableTool(TOOLBAR_START_WATCHMODE, false);
		getController()->startWatchMode();
		toolbar->EnableTool(TOOLBAR_STOP_WATCHMODE, true);
		wxThreadEvent tEvt;
		refreshField(tEvt);
	}
	
}

void MountainCarWindow::render(wxDC& dc)
{ 
	// draw some text
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.SetBackgroundMode(wxSOLID);

	dc.Clear();

	int width, height;
	double pos = getController()->getPosition(); 
	double vel = getController()->getVelocity();
	int action = getController()->getAction();
	panel->GetClientSize(&width, &height);

	dc.DrawCircle((pos - -1.2) / 1.8 * width, height / 2, 20 / 2);

	dc.DrawRectangle(width / 2, height / 6 * 4, vel * width / 2, 20);

	if (action == -1)
		dc.DrawCircle(width / 4, height / 6 * 5, 20);
	else if (action == 1)
		dc.DrawCircle(width / 4 * 3, height / 6 * 5, 20);
}

std::string MountainCarWindow::getLabel()
{
	return "PongGame";
}

MountainCarController* MountainCarWindow::getController()
{
	return static_cast<MountainCarController*>(controller);
}
