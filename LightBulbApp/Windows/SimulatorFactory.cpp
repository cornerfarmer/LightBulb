// Includes
#include "Windows/SimulatorFactory.hpp"
#include "SimulatorController.hpp"

SimulatorFactory::SimulatorFactory(NeuralNetworkRepository* neuralNetworkRepository_)
{
	neuralNetworkRepository = neuralNetworkRepository_;
}

AbstractSubApp* SimulatorFactory::createWindow(AbstractWindow* parent)
{
	SimulatorController* controller = new SimulatorController(neuralNetworkRepository, parent);
	controller->getWindow()->Show();
	return controller;
}

std::string SimulatorFactory::getLabel()
{
	return SimulatorController::getLabel();
}
