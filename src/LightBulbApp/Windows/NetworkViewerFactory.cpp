// Includes
#include "LightBulbApp/LightBulbAppPrec.hpp"
#include "LightBulbApp/Windows/NetworkViewerFactory.hpp"
#include "LightBulbApp/Windows/NetworkViewerController.hpp"
#include "LightBulbApp/Windows/NetworkViewerWindow.hpp"

namespace LightBulb
{
	NetworkViewerFactory::NetworkViewerFactory(NeuralNetworkRepository& neuralNetworkRepository_)
	{
		neuralNetworkRepository = &neuralNetworkRepository_;
	}

	AbstractSubApp* NetworkViewerFactory::createSupApp(AbstractMainApp& mainApp, AbstractWindow& parent) const
	{
		NetworkViewerController* controller = new NetworkViewerController(mainApp, *neuralNetworkRepository, parent);
		controller->getWindow().Show();
		return controller;
	}

	std::string NetworkViewerFactory::getLabel() const
	{
		return NetworkViewerController::getLabel();
	}
}
