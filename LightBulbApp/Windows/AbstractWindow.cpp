// Includes
#include "Windows/AbstractWindow.hpp"
#include "AbstractSubApp.hpp"


AbstractWindow::AbstractWindow(AbstractApp* controller_, std::string label, AbstractWindow* parent)
	: wxFrame(parent, wxID_ANY, label, wxDefaultPosition, wxDefaultSize)
{
	controller = controller_;
}

void AbstractWindow::refreshAfterChange(wxSizer* sizer)
{
	wxSize clientSize = sizer->ComputeFittingClientSize(this);
	SetMinClientSize(clientSize);
	SetSize(GetSize());
	Layout();
}
