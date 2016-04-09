// Includes
#include "Windows/AbstractWindow.hpp"


AbstractWindow::AbstractWindow(std::string label, AbstractWindow* parent)
	: wxFrame(parent, wxID_ANY, label)
{

}

void AbstractWindow::refreshAfterChange(wxSizer* sizer)
{
	wxSize clientSize = sizer->ComputeFittingClientSize(this);
	SetMinClientSize(clientSize);
	SetSize(GetSize());
	Layout();
}