// Includes
#include "Windows/TrainingController.hpp"
#include <NetworkTopology/FeedForwardNetworkTopology.hpp>
#include <NeuralNetwork/NeuralNetwork.hpp>
#include "TrainingWindow.hpp"
#include <Repositories/NeuralNetworkRepository.hpp>
#include <Repositories/TrainingPlanRepository.hpp>
#include <fstream>
#include "IO/UsedArchives.hpp"
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>
#include "PreferencesController.hpp"
#include <TrainingPlans/AbstractSingleNNTrainingPlan.hpp>
#include <TrainingPlans/AbstractEvolutionTrainingPlan.hpp>
#include <Learning/Evolution/EvolutionLearningResult.hpp>


TrainingController::TrainingController(NeuralNetworkRepository* neuralNetworkRepository_, TrainingPlanRepository* trainingPlanRepository_, std::vector<AbstractTrainingPlan*>& trainingPlanPatterns_)
{
	neuralNetworkRepository = neuralNetworkRepository_;
	trainingPlanRepository = trainingPlanRepository_;
	neuralNetworkRepository->registerObserver(EVT_NN_CHANGED, &TrainingController::neuralNetworksChanged, this);
	trainingPlanRepository->registerObserver(EVT_TP_CHANGED, &TrainingController::trainingPlansChanged, this);

	window.reset(new TrainingWindow(this));;
	saveTrainingPlanAfterPausedIndex = -1;
	saveTrainingSessionAfterPause = false;

	for (int i = 0; i < trainingPlanPatterns_.size(); i++)
	{
		trainingPlanPatterns.push_back(std::unique_ptr<AbstractTrainingPlan>(trainingPlanPatterns_[i]));
	}

	wxThreadEvent evt(TW_EVT_REFRESH_ALL);
	window->GetEventHandler()->QueueEvent(evt.Clone());
}

std::vector<std::unique_ptr<AbstractNeuralNetwork>>* TrainingController::getNeuralNetworks()
{
	return neuralNetworkRepository->getNeuralNetworks();
}

std::vector<std::unique_ptr<AbstractTrainingPlan>>* TrainingController::getTrainingPlanPatterns()
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

	std::string defaultName = trainingPlan->getDefaultName();
	int index = 1;
	while (trainingPlanRepository->getByName(defaultName + " #" + std::to_string(index)))
	{
		index++;
	}
	trainingPlan->setName(defaultName + " #" + std::to_string(index));

	trainingPlanRepository->Add(trainingPlan);

	AbstractSingleNNTrainingPlan* singleNNTrainingPlan = dynamic_cast<AbstractSingleNNTrainingPlan*>(trainingPlan);
	if (singleNNTrainingPlan)
	{
		if (getNeuralNetworks()->size() <= neuralNetworkIndex)
		{
			singleNNTrainingPlan->start();
			neuralNetworkRepository->Add(singleNNTrainingPlan->getNeuralNetwork());
		}
		else
		{
			singleNNTrainingPlan->setNeuralNetwork((*getNeuralNetworks())[neuralNetworkIndex].get());
			singleNNTrainingPlan->start();
		}
	}
	else
	{
		trainingPlan->start();
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
		if (trainingPlanPatterns[i].get() == trainingPlanPattern)
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
	if (dynamic_cast<AbstractEvolutionTrainingPlan*>(trainingPlan))
	{
		EvolutionLearningResult* learningResult = static_cast<EvolutionLearningResult*>(static_cast<AbstractEvolutionTrainingPlan*>(trainingPlan)->getLearningResult());
		AbstractNeuralNetwork* clone = learningResult->bestObjects.front()->getNeuralNetwork()->clone();
		clone->setName("Result of " + trainingPlan->getName());
		neuralNetworkRepository->Add(clone);
	}
	wxThreadEvent evt(TW_EVT_REFRESH_TP);
	window->GetEventHandler()->QueueEvent(evt.Clone());
}

void TrainingController::resumeTrainingPlan(AbstractTrainingPlan* trainingPlan)
{
	trainingPlan->start();
	wxThreadEvent evt(TW_EVT_REFRESH_TP);
	window->GetEventHandler()->QueueEvent(evt.Clone());
}

void TrainingController::show()
{
	window->Show();
}

TrainingWindow* TrainingController::getWindow()
{
	return window.get();
}

void TrainingController::addSubAppFactory(AbstractSubAppFactory* newSubAppFactory)
{
	subAppFactories.push_back(newSubAppFactory);
	window->addSubAppFactory(newSubAppFactory, subAppFactories.size() - 1);
}

int TrainingController::getIndexOfNeuralNetwork(AbstractNeuralNetwork* network)
{
	return neuralNetworkRepository->getIndexOfNeuralNetwork(network);
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
	if (trainingPlan->isRunning()) 
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
	AbstractTrainingPlan* trainingPlan = trainingPlanRepository->load(path);
	if (dynamic_cast<AbstractSingleNNTrainingPlan*>(trainingPlan))
	{
		neuralNetworkRepository->Add(static_cast<AbstractSingleNNTrainingPlan*>(trainingPlan)->getNeuralNetwork());
	}
}

void TrainingController::loadTrainingSession(std::string path)
{
	std::ifstream is(path);
	cereal::XMLInputArchive archive(is);

	archive(*this);

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

void TrainingController::addSubApp(int subAppFactoryIndex)
{
	activeSubApps.push_back(std::unique_ptr<AbstractSubApp>(subAppFactories[subAppFactoryIndex]->createSupApp(this, window.get())));
}

void TrainingController::openPreferences(int trainingPlanPatternIndex)
{
	PreferencesController* preferencesController = new PreferencesController(this, trainingPlanPatterns[trainingPlanPatternIndex].get(), window.get());
	preferencesController->getWindow()->Show();
	activeSubApps.push_back(std::unique_ptr<AbstractSubApp>(preferencesController));
}

void TrainingController::setTrainingPlanName(int trainingPlanIndex, std::string newName)
{
	trainingPlanRepository->setTrainingPlanName(trainingPlanIndex, newName);
}

void TrainingController::removeSubApp(AbstractSubApp* subApp)
{
	for (auto activeSubApp = activeSubApps.begin(); activeSubApp != activeSubApps.end(); activeSubApp++)
	{
		if (activeSubApp->get() == subApp)
		{
			activeSubApps.erase(activeSubApp);
			break;
		}
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

