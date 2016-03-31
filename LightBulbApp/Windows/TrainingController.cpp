// Includes
#include "Windows/TrainingController.hpp"
#include <NetworkTopology/LayeredNetwork.hpp>
#include <NeuralNetwork/NeuralNetwork.hpp>
#include "TrainingPlans/ExampleTrainingPlan.hpp"
#include "Examples/BackpropagationXorExample.hpp"
#include "TrainingWindow.hpp"
#include <Examples/BackpropagationXorExample.hpp>
#include <Repositories/NeuralNetworkRepository.hpp>

TrainingController::TrainingController(NeuralNetworkRepository* neuralNetworkRepository_)
{
	neuralNetworkRepository = neuralNetworkRepository_;
	neuralNetworkRepository->registerObserver(EVT_NN_CHANGED, &TrainingController::neuralNetworksChanged, this);

	window.reset(new TrainingWindow(this));;
	logger = NULL;

	trainingPlanPatterns.push_back(new ExampleTrainingPlan());
	trainingPlanPatterns.push_back(new BackpropagationXorExample());
	window->refreshAllData();
}

std::vector<std::unique_ptr<AbstractNeuralNetwork>>* TrainingController::getNeuralNetworks()
{
	return neuralNetworkRepository->getNeuralNetworks();
}

std::vector<AbstractTrainingPlan*>* TrainingController::getTrainingPlanPatterns()
{
	return &trainingPlanPatterns;
}

std::vector<AbstractTrainingPlan*>* TrainingController::getTrainingPlans()
{
	return &trainingPlans;
}

void TrainingController::startTrainingPlanPattern(int trainingPlanPatternIndex, int neuralNetworkIndex)
{
	trainingPlans.push_back(trainingPlanPatterns[trainingPlanPatternIndex]->getCopyForExecute());
	trainingPlans.back()->registerObserver(EVT_TP_PAUSED, &TrainingController::trainingPlanPaused, this);
	trainingPlans.back()->registerObserver(EVT_TP_FINISHED, &TrainingController::trainingPlanFinished, this);
	trainingPlans.back()->setLogger(logger);
	if (getNeuralNetworks()->size() <= neuralNetworkIndex) 
	{
		trainingPlans.back()->start();
		neuralNetworkRepository->Add(trainingPlans.back()->getNeuralNetwork());
	} 
	else
	{
		trainingPlans.back()->start((*getNeuralNetworks())[neuralNetworkIndex].get());
	}
	window->refreshTrainingPlans();
}

void TrainingController::neuralNetworksChanged(NeuralNetworkRepository* neuralNetworkRepository)
{
	window->refreshNeuralNetworks();
}

void TrainingController::pauseTrainingPlan(AbstractTrainingPlan* trainingPlan)
{
	trainingPlan->pause();
	window->refreshTrainingPlans();
}

int TrainingController::getIndexOfTrainingPlanPattern(AbstractTrainingPlan* trainingPlanPattern)
{
	for (int i = 0; i < trainingPlanPatterns.size(); i++)
	{
		if (trainingPlanPatterns[i] == trainingPlanPattern)
			return i;
	}
	return -1;
}

void TrainingController::trainingPlanPaused(AbstractTrainingPlan* trainingPlan)
{
	window->refreshTrainingPlans();
}

void TrainingController::trainingPlanFinished(AbstractTrainingPlan* trainingPlan)
{
	window->refreshTrainingPlans();
}

void TrainingController::resumeTrainingPlan(AbstractTrainingPlan* trainingPlan)
{
	trainingPlan->start();
	window->refreshTrainingPlans();
}

void TrainingController::setLogger(AbstractLogger* newLogger)
{
	logger = newLogger;
}

void TrainingController::show()
{
	window->Show();
}

TrainingWindow* TrainingController::getWindow()
{
	return window.get();
}

int TrainingController::getIndexOfNeuralNetwork(AbstractNeuralNetwork* network)
{
	return neuralNetworkRepository->getIndexOfNeuralNetwork(network);
}

void TrainingController::addSubWindow(AbstractWindow* newSubWindow)
{
	window->addSubWindow(newSubWindow);
}

void TrainingController::saveNeuralNetwork(std::string path, int neuralNetworkIndex)
{
	neuralNetworkRepository->save(path, neuralNetworkIndex);
}

void TrainingController::loadNeuralNetwork(std::string path)
{
	neuralNetworkRepository->load(path);
}
