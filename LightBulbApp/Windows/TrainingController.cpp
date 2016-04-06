// Includes
#include "Windows/TrainingController.hpp"
#include <NetworkTopology/LayeredNetwork.hpp>
#include <NeuralNetwork/NeuralNetwork.hpp>
#include "TrainingPlans/ExampleTrainingPlan.hpp"
#include "Examples/BackpropagationXorExample.hpp"
#include "TrainingWindow.hpp"
#include <Examples/BackpropagationXorExample.hpp>
#include <Repositories/NeuralNetworkRepository.hpp>
#include <Repositories/TrainingPlanRepository.hpp>
#include <fstream>
#include <cereal/archives/xml.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>
#include "IO/TrainingControllerIO.hpp"


TrainingController::TrainingController(NeuralNetworkRepository* neuralNetworkRepository_, TrainingPlanRepository* trainingPlanRepository_)
{
	neuralNetworkRepository = neuralNetworkRepository_;
	trainingPlanRepository = trainingPlanRepository_;
	neuralNetworkRepository->registerObserver(EVT_NN_CHANGED, &TrainingController::neuralNetworksChanged, this);
	trainingPlanRepository->registerObserver(EVT_TP_CHANGED, &TrainingController::trainingPlansChanged, this);

	window.reset(new TrainingWindow(this));;
	logger = NULL;
	saveTrainingPlanAfterPausedIndex = -1;
	saveTrainingSessionAfterPause = false;

	trainingPlanPatterns.push_back(new ExampleTrainingPlan());
	trainingPlanPatterns.push_back(new BackpropagationXorExample());

	wxThreadEvent evt(TW_EVT_REFRESH_ALL);
	window->GetEventHandler()->QueueEvent(evt.Clone());
}

std::vector<std::unique_ptr<AbstractNeuralNetwork>>* TrainingController::getNeuralNetworks()
{
	return neuralNetworkRepository->getNeuralNetworks();
}

std::vector<AbstractTrainingPlan*>* TrainingController::getTrainingPlanPatterns()
{
	return &trainingPlanPatterns;
}

std::vector<std::unique_ptr<AbstractTrainingPlan>>* TrainingController::getTrainingPlans()
{
	return trainingPlanRepository->getTrainingPlans();
}

void TrainingController::startTrainingPlanPattern(int trainingPlanPatternIndex, int neuralNetworkIndex)
{

	AbstractTrainingPlan* trainingPlan = trainingPlanPatterns[trainingPlanPatternIndex]->getCopyForExecute();
	trainingPlan->registerObserver(EVT_TP_PAUSED, &TrainingController::trainingPlanPaused, this);
	trainingPlan->registerObserver(EVT_TP_FINISHED, &TrainingController::trainingPlanFinished, this);
	trainingPlan->setLogger(logger);
	trainingPlanRepository->Add(trainingPlan);
	if (getNeuralNetworks()->size() <= neuralNetworkIndex) 
	{
		trainingPlan->start();
		neuralNetworkRepository->Add(trainingPlan->getNeuralNetwork());
	} 
	else
	{
		trainingPlan->start((*getNeuralNetworks())[neuralNetworkIndex].get());
	}
	wxThreadEvent evt(TW_EVT_REFRESH_TP);
	window->GetEventHandler()->QueueEvent(evt.Clone());
}

void TrainingController::neuralNetworksChanged(NeuralNetworkRepository* neuralNetworkRepository)
{
	wxThreadEvent evt(TW_EVT_REFRESH_NN);
	window->GetEventHandler()->QueueEvent(evt.Clone());
}

void TrainingController::trainingPlansChanged(TrainingPlanRepository* trainingPlanRepository)
{
	wxThreadEvent evt(TW_EVT_REFRESH_TP);
	window->GetEventHandler()->QueueEvent(evt.Clone());
}

void TrainingController::pauseTrainingPlan(AbstractTrainingPlan* trainingPlan)
{
	trainingPlan->pause();
	wxThreadEvent evt(TW_EVT_REFRESH_TP);
	window->GetEventHandler()->QueueEvent(evt.Clone());
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
	wxThreadEvent evt(TW_EVT_REFRESH_TP);
	window->GetEventHandler()->QueueEvent(evt.Clone());
	if (saveTrainingPlanAfterPausedIndex != -1 && (*trainingPlanRepository->getTrainingPlans())[saveTrainingPlanAfterPausedIndex].get() == trainingPlan)
	{
		wxThreadEvent evt(TW_EVT_SAVE_TP);
		evt.SetPayload(saveTrainingPlanAfterPausedIndex);
		window->GetEventHandler()->QueueEvent(evt.Clone());
		saveTrainingPlanAfterPausedIndex = -1;
	}
	if (saveTrainingSessionAfterPause && allTrainingPlansPaused())
	{
		wxThreadEvent evt(TW_EVT_SAVE_TS);
		window->GetEventHandler()->QueueEvent(evt.Clone());
		saveTrainingSessionAfterPause = false;
	}
}

void TrainingController::trainingPlanFinished(AbstractTrainingPlan* trainingPlan)
{
	wxThreadEvent evt(TW_EVT_REFRESH_TP);
	window->GetEventHandler()->QueueEvent(evt.Clone());
}

void TrainingController::resumeTrainingPlan(AbstractTrainingPlan* trainingPlan)
{
	trainingPlan->start();
	wxThreadEvent evt(TW_EVT_REFRESH_TP);
	window->GetEventHandler()->QueueEvent(evt.Clone());
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

void TrainingController::saveTrainingPlan(int trainingPlanIndex)
{
	AbstractTrainingPlan* trainingPlan = (*trainingPlanRepository->getTrainingPlans())[trainingPlanIndex].get();
	if (!trainingPlan->isPaused()) 
	{
		saveTrainingPlanAfterPausedIndex = trainingPlanIndex;
		trainingPlan->pause();
	}
	else
	{
		wxThreadEvent evt(TW_EVT_SAVE_TP);
		evt.SetPayload(trainingPlanIndex);
		window->GetEventHandler()->QueueEvent(evt.Clone());
	}
}

void TrainingController::saveTrainingPlan(std::string path, int trainingPlanIndex)
{
	trainingPlanRepository->save(path, trainingPlanIndex);
}

void TrainingController::loadTrainingPlan(std::string path)
{
	AbstractTrainingPlan* trainingPlan = trainingPlanRepository->load(path, logger);
	neuralNetworkRepository->Add(trainingPlan->getNeuralNetwork());
}

void TrainingController::loadTrainingSession(std::string path)
{
	std::ifstream is(path);
	cereal::XMLInputArchive archive(is);

	archive(*this);

	for (auto trainingPlan = trainingPlanRepository->getTrainingPlans()->begin(); trainingPlan != trainingPlanRepository->getTrainingPlans()->end(); trainingPlan++)
	{
		(*trainingPlan)->setLogger(logger);
	}

	wxThreadEvent evt(TW_EVT_REFRESH_ALL);
	window->GetEventHandler()->QueueEvent(evt.Clone());
}

void TrainingController::saveTrainingSession(std::string path)
{
	std::ofstream os(path);
	cereal::XMLOutputArchive archive(os);

	archive(*this);
}

void TrainingController::saveTrainingSession()
{
	if (!allTrainingPlansPaused())
	{
		saveTrainingSessionAfterPause = true;
		for (auto trainingPlan = trainingPlanRepository->getTrainingPlans()->begin(); trainingPlan != trainingPlanRepository->getTrainingPlans()->end(); trainingPlan++)
		{
			if (!(*trainingPlan)->isPaused())
				(*trainingPlan)->pause();
		}
	}
	else
	{
		wxThreadEvent evt(TW_EVT_SAVE_TS);
		window->GetEventHandler()->QueueEvent(evt.Clone());
	}
}



bool TrainingController::allTrainingPlansPaused()
{
	bool allPaused = true;
	for (auto trainingPlan = trainingPlanRepository->getTrainingPlans()->begin(); trainingPlan != trainingPlanRepository->getTrainingPlans()->end(); trainingPlan++)
	{
		if (!(*trainingPlan)->isPaused())
			allPaused = false;
	}
	return allPaused;
}