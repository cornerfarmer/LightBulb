// Includes
#include "LightBulbExamplePrec.hpp"
#include "Examples/TicTacToeEvolution/TicTacToeGameWindow.hpp"
#include "TicTacToeGameController.hpp"

BEGIN_EVENT_TABLE(TicTacToeGameWindow, wxFrame)
EVT_PAINT(TicTacToeGameWindow::paintEvent)
EVT_SIZE(TicTacToeGameWindow::resize)
END_EVENT_TABLE()

wxDEFINE_EVENT(TTT_EVT_FIELD_CHANGED, wxThreadEvent);

enum
{
	TOOLBAR_STOP_STEPMODE,
	TOOLBAR_START_STEPMODE,
	TOOLBAR_DO_STEP,
};

TicTacToeGameWindow::TicTacToeGameWindow(TicTacToeGameController& controller_, AbstractWindow& parent)
	:AbstractSubAppWindow(controller_, getLabel(), parent)
{
	panel = nullptr;
	Bind(TTT_EVT_FIELD_CHANGED, &TicTacToeGameWindow::refreshField, this);

	toolbar = CreateToolBar();
	toolbar->AddTool(TOOLBAR_STOP_STEPMODE, "StepMode Off", wxArtProvider::GetBitmap(wxART_GO_FORWARD));
	toolbar->AddTool(TOOLBAR_START_STEPMODE, "StepMode On", wxArtProvider::GetBitmap(wxART_DELETE));
	toolbar->AddTool(TOOLBAR_DO_STEP, "Step", wxArtProvider::GetBitmap(wxART_GOTO_LAST));
	toolbar->Bind(wxEVT_TOOL, wxCommandEventFunction(&TicTacToeGameWindow::toolBarClicked), this);
	toolbar->Realize();

	toolbar->EnableTool(TOOLBAR_START_STEPMODE, true);
	toolbar->EnableTool(TOOLBAR_STOP_STEPMODE, false);
	toolbar->EnableTool(TOOLBAR_DO_STEP, false);

	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	panel = new wxPanel(this);
	panel->SetMinSize(wxSize(300, 300));

	sizer->Add(panel, 1, wxEXPAND);
	SetSizerAndFit(sizer);
}

void TicTacToeGameWindow::paintEvent(wxPaintEvent& evt)
{
	paintNow();
}

void TicTacToeGameWindow::resize(wxSizeEvent& evt)
{
	Layout();
	paintNow();
}

void TicTacToeGameWindow::paintNow()
{
	if (panel)
	{
		wxClientDC dc(panel);
		render(dc);
	}
}

void TicTacToeGameWindow::refreshField(wxThreadEvent& evt)
{
	currentFields = getController().getFields();
	paintNow();
}

void TicTacToeGameWindow::toolBarClicked(wxCommandEvent& evt)
{
	if (evt.GetId() == TOOLBAR_STOP_STEPMODE)
	{
		toolbar->EnableTool(TOOLBAR_STOP_STEPMODE, false);
		toolbar->EnableTool(TOOLBAR_DO_STEP, false);
		getController().stopStepMode();
		toolbar->EnableTool(TOOLBAR_START_STEPMODE, true);

		currentFields.clear();
		paintNow();
	}
	else if (evt.GetId() == TOOLBAR_START_STEPMODE)
	{
		toolbar->EnableTool(TOOLBAR_START_STEPMODE, false);
		getController().startStepMode();
		toolbar->EnableTool(TOOLBAR_STOP_STEPMODE, true);
		toolbar->EnableTool(TOOLBAR_DO_STEP, true);
		wxThreadEvent tEvt;
		refreshField(tEvt);
	}
	else if (evt.GetId() == TOOLBAR_DO_STEP)
	{
		getController().doStep();
	}
	
}

void TicTacToeGameWindow::render(wxDC& dc)
{ 
	// draw some text
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.SetBackgroundMode(wxSOLID);

	dc.Clear();

	int width, height;
	panel->GetClientSize(&width, &height);

	dc.DrawLine(width / 3, 0, width / 3, height);
	dc.DrawLine(width / 3 * 2, 0, width / 3 * 2, height);

	dc.DrawLine(0, height / 3, width, height / 3);
	dc.DrawLine(0, height / 3 * 2, width, height / 3 * 2);

	for (int x = 0; x < currentFields.size(); x++)
	{
		for (int y = 0; y < currentFields[x].size(); y++)
		{
			if (currentFields[x][y] == 1)
			{
				dc.DrawLine(x * width / 3, y * height / 3, (x + 1) * width / 3, (y + 1) * height / 3);
				dc.DrawLine((x + 1) * width / 3, y * height / 3, x * width / 3, (y + 1) * height / 3);
			}
			else if (currentFields[x][y] == -1)
			{
				dc.DrawEllipse(x * width / 3, y * height / 3, width / 3, height / 3);
			}
		}
	}
}

std::string TicTacToeGameWindow::getLabel()
{
	return "TicTacToeGame";
}

TicTacToeGameController& TicTacToeGameWindow::getController()
{
	return static_cast<TicTacToeGameController&>(*controller);
}
