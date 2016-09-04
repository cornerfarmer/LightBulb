// Includes
#include "Examples/Nature/NatureWindow.hpp"
#include "NatureController.hpp"
#include <wx/artprov.h>
#include <Examples/TicTacToeEvolution/TicTacToeGameWindow.hpp>

BEGIN_EVENT_TABLE(NatureWindow, wxFrame)
EVT_PAINT(NatureWindow::paintEvent)
EVT_SIZE(NatureWindow::resize)
END_EVENT_TABLE()

wxDEFINE_EVENT(NATURE_EVT_FIELD_CHANGED, wxThreadEvent);

enum
{
	TOOLBAR_STOP_WATCHMODE,
	TOOLBAR_START_WATCHMODE,
};

NatureWindow::NatureWindow(NatureController* controller_, AbstractWindow* parent)
	:AbstractSubAppWindow(controller_, NatureWindow::getLabel(), parent)
{
	panel = NULL;
	Bind(NATURE_EVT_FIELD_CHANGED, &NatureWindow::refreshField, this);

	toolbar = CreateToolBar();
	toolbar->AddTool(TOOLBAR_STOP_WATCHMODE, "WatchMode Off", wxArtProvider::GetBitmap(wxART_GO_FORWARD));
	toolbar->AddTool(TOOLBAR_START_WATCHMODE, "WatchMode On", wxArtProvider::GetBitmap(wxART_DELETE));
	toolbar->Bind(wxEVT_TOOL, wxCommandEventFunction(&NatureWindow::toolBarClicked), this);
	toolbar->Realize();

	toolbar->EnableTool(TOOLBAR_START_WATCHMODE, true);
	toolbar->EnableTool(TOOLBAR_STOP_WATCHMODE, false);

	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	panel = new wxPanel(this);
	panel->SetMinSize(wxSize(300, 300));
	
	sizer->Add(panel, 1, wxEXPAND);
	SetSizerAndFit(sizer);
}

void NatureWindow::paintEvent(wxPaintEvent& evt)
{
	paintNow();
}

void NatureWindow::resize(wxSizeEvent& evt)
{
	Layout();
	paintNow();
}

void NatureWindow::paintNow()
{
	if (panel)
	{
		wxClientDC dc(panel);
		render(dc);
	}
}

void NatureWindow::refreshField(wxThreadEvent& evt)
{
	paintNow();
}

void NatureWindow::toolBarClicked(wxCommandEvent& evt)
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

void NatureWindow::render(wxDC& dc)
{ 
	// draw some text
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.SetBackgroundMode(wxSOLID);

	dc.Clear();
	dc.SetPen(*wxTRANSPARENT_PEN);

	int width, height;
	auto tiles = getController()->getTiles(); 
	if (tiles->size() > 0 && tiles->front().size() > 0)
	{
		panel->GetClientSize(&width, &height);
		int tileWidth = width / tiles->size();
		int tileHeight = height / tiles->front().size();
		int tileSize = std::min(tileWidth, tileHeight);

		for (int x = 0; x < tiles->size(); x++)
		{
			for (int y = 0; y < tiles->at(x).size(); y++)
			{
				if (tiles->at(x)[y]) {
					dc.SetBrush(*tiles->at(x)[y]);
					dc.DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize);
				}
			}
		}
	}

	getController()->renderingFinished();
}

std::string NatureWindow::getLabel()
{
	return "PongGame";
}

NatureController* NatureWindow::getController()
{
	return static_cast<NatureController*>(controller);
}
