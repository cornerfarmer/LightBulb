// Includes
#include "LightBulbApp/LightBulbAppPrec.hpp"
#include "LightBulbApp/Windows/AbstractSubApp.hpp"
#include "LightBulbApp/Windows/AbstractMainApp.hpp"

namespace LightBulb
{
	AbstractSubApp::AbstractSubApp(AbstractMainApp& mainApp_)
	{
		mainApp = &mainApp_;
	}

	void AbstractSubApp::close()
	{
		prepareClose();
		mainApp->removeSubApp(*this);
	}
}