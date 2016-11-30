// Includes
#include "Windows/AbstractSubAppWindow.hpp"
#include "Windows/AbstractSubApp.hpp"

namespace LightBulb
{
	AbstractSubAppWindow::AbstractSubAppWindow(AbstractSubApp& controller_, std::string label, AbstractWindow& parent)
		: AbstractWindow(controller_, label, &parent)
	{
		Bind(wxEVT_CLOSE_WINDOW, wxCloseEventFunction(&AbstractSubAppWindow::close), this);
	}


	void AbstractSubAppWindow::close(wxCloseEvent& event)
	{
		getController()->close();

		event.Skip();
	}

	AbstractSubApp* AbstractSubAppWindow::getController()
	{
		return static_cast<AbstractSubApp*>(controller);
	}
}
