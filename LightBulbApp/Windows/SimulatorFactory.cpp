// Includes
#include "Windows/SimulatorFactory.hpp"
#include "SimulatorController.hpp"

SimulatorFactory::SimulatorFactory(NeuralNetworkRepository* neuralNetworkRepository_)
{
	neuralNetworkRepository = neuralNetworkRepository_;
}

AbstractSubApp* SimulatorFactory::createSupApp(AbstractMainApp* mainApp, AbstractWindow* parent)
{
	SimulatorController* controller = new SimulatorController(mainApp, neuralNetworkRepository, parent);
	controller->getWindow()->Show();
	return controller;
}

std::string SimulatorFactory::getLabel()
{
	return SimulatorController::getLabel();
}
