// Includes
#include "Windows/NetworkViewerFactory.hpp"
#include "NetworkViewerController.hpp"

NetworkViewerFactory::NetworkViewerFactory(NeuralNetworkRepository* neuralNetworkRepository_)
{
	neuralNetworkRepository = neuralNetworkRepository_;
}

AbstractSubApp* NetworkViewerFactory::createSupApp(AbstractMainApp* mainApp, AbstractWindow* parent)
{
	NetworkViewerController* controller = new NetworkViewerController(mainApp, neuralNetworkRepository, parent);
	controller->getWindow()->Show();
	return controller;
}

std::string NetworkViewerFactory::getLabel()
{
	return NetworkViewerController::getLabel();
}
