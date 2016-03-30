#include "App.hpp"
#include "Windows/TrainingController.hpp"
#include "Windows/LoggerController.hpp"
#include "Windows/SimulatorController.hpp"
#include "Repositories/NeuralNetworkRepository.hpp"

bool App::OnInit()
{
	NeuralNetworkRepository* neuralNetworkRepository = new NeuralNetworkRepository();

	TrainingController* trainingController = new TrainingController(neuralNetworkRepository);
	LoggerController* loggerController = new LoggerController(trainingController->getWindow());
	SimulatorController* simulatorController = new SimulatorController(neuralNetworkRepository, trainingController->getWindow());

	trainingController->addSubWindow(loggerController->getWindow());
	trainingController->setLogger(loggerController);
	trainingController->addSubWindow(simulatorController->getWindow());

	trainingController->show();
	return true;
}
