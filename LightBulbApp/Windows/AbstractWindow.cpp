// Includes
#include "Windows/AbstractWindow.hpp"

AbstractWindow::AbstractWindow(std::string label, AbstractWindow* parent)
	: wxFrame(parent, wxID_ANY, label)
{

}
