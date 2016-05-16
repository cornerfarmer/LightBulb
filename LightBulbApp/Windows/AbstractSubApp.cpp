// Includes
#include "Windows/AbstractSubApp.hpp"
#include "Windows/AbstractMainApp.hpp"

AbstractSubApp::AbstractSubApp(AbstractMainApp* mainApp_)
{
	mainApp = mainApp_;
}

void AbstractSubApp::close()
{
	prepareClose();
	mainApp->removeSubApp(this);
}
