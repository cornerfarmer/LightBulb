// Includes
#include "Graphics/TrainingWindow.hpp"
#include <wx/dataview.h>

BEGIN_EVENT_TABLE(TrainingWindow, wxFrame)
EVT_BUTTON(wxID_NEW, TrainingWindow::OnClick)
END_EVENT_TABLE()

TrainingWindow::TrainingWindow()
{
	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(new wxButton(this, -1, "A Really Really Big Button"), 1, 0, 0);

	wxDataViewListCtrl *listctrl = new wxDataViewListCtrl(this, wxID_ANY);
	listctrl->AppendToggleColumn("Toggle");
	listctrl->AppendTextColumn("Text");
	wxVector<wxVariant> data;
	data.push_back(wxVariant(true));
	data.push_back(wxVariant("row 1"));
	listctrl->AppendItem(data);
	data.clear();
	data.push_back(wxVariant(false));
	data.push_back(wxVariant("row 3"));
	listctrl->AppendItem(data);


	sizer->Add(listctrl, 4, wxEXPAND, 0);
	sizer->SetSizeHints(this);
	SetSizer(sizer);
}

void TrainingWindow::OnClick(wxCommandEvent& event)
{
	wxMessageBox("This is a wxWidgets' Hello world sample", "About Hello World", wxOK | wxICON_INFORMATION);
}
