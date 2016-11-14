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

namespace LightBulb
{
	TrainingController::TrainingController(NeuralNetworkRepository& neuralNetworkRepository_, TrainingPlanRepository& trainingPlanRepository_, std::vector<AbstractTrainingPlan*>& trainingPlanPatterns_)
	{
		neuralNetworkRepository = &neuralNetworkRepository_;
		trainingPlanRepository = &trainingPlanRepository_;
		neuralNetworkRepository->registerObserver(EVT_NN_CHANGED, &TrainingController::neuralNetworksChanged, *this);
		trainingPlanRepository->registerObserver(EVT_TP_CHANGED, &TrainingController::trainingPlansChanged, *this);

		window = new TrainingWindow(*this);
		saveTrainingPlanAfterPausedIndex = -1;
		saveTrainingSessionAfterPause = false;
		closeWindowAfterPause = false;

		for (int i = 0; i < trainingPlanPatterns_.size(); i++)
		{
			trainingPlanPatterns.push_back(std::unique_ptr<AbstractTrainingPlan>(trainingPlanPatterns_[i]));
		}

		wxThreadEvent evt(TW_EVT_REFRESH_ALL);
		window->GetEventHandler()->QueueEvent(evt.Clone());
	}

	const std::vector<std::unique_ptr<AbstractNeuralNetwork>>& TrainingController::getNeuralNetworks() const
	{
		return neuralNetworkRepository->getNeuralNetworks();
	}

	const std::vector<std::unique_ptr<AbstractTrainingPlan>>& TrainingController::getTrainingPlanPatterns() const
	{
		return trainingPlanPatterns;
	}

	const std::vector<std::unique_ptr<AbstractTrainingPlan>>& TrainingController::getTrainingPlans() const
	{
		return trainingPlanRepository->getTrainingPlans();
	}

	void TrainingController::startTrainingPlanPattern(int trainingPlanPatternIndex)
	{

		AbstractTrainingPlan* trainingPlan = trainingPlanPatterns[trainingPlanPatternIndex]->getCopyForExecute();
		trainingPlan->registerObserver(EVT_TP_PAUSED, &TrainingController::trainingPlanPaused, *this);
		trainingPlan->registerObserver(EVT_TP_FINISHED, &TrainingController::trainingPlanFinished, *this);

		std::string defaultName = trainingPlan->getDefaultName();
		int index = 1;
		while (trainingPlanRepository->exists(defaultName + " #" + std::to_string(index)))
		{
			index++;
		}
		trainingPlan->setName(defaultName + " #" + std::to_string(index));

		trainingPlanRepository->Add(trainingPlan);

		AbstractSingleNNTrainingPlan* singleNNTrainingPlan = dynamic_cast<AbstractSingleNNTrainingPlan*>(trainingPlan);
		if (singleNNTrainingPlan)
		{
			singleNNTrainingPlan->start();
			neuralNetworkRepository->Add(&singleNNTrainingPlan->getNeuralNetwork());
		}
		else
		{
			trainingPlan->start();
		}

		wxThreadEvent evt(TW_EVT_REFRESH_TP);
		window->GetEventHandler()->QueueEvent(evt.Clone());
	}

	void TrainingController::neuralNetworksChanged(NeuralNetworkRepository& neuralNetworkRepository)
	{
		wxThreadEvent evt(TW_EVT_REFRESH_NN);
		window->GetEventHandler()->QueueEvent(evt.Clone());
	}

	void TrainingController::trainingPlansChanged(TrainingPlanRepository& trainingPlanRepository)
	{
		wxThreadEvent evt(TW_EVT_REFRESH_TP);
		window->GetEventHandler()->QueueEvent(evt.Clone());
	}

	void TrainingController::pauseTrainingPlan(AbstractTrainingPlan& trainingPlan)
	{
		trainingPlan.pause();
		wxThreadEvent evt(TW_EVT_REFRESH_TP);
		window->GetEventHandler()->QueueEvent(evt.Clone());
	}

	int TrainingController::getIndexOfTrainingPlanPatternWithName(const std::string& name) const
	{
		for (int i = 0; i < trainingPlanPatterns.size(); i++)
		{
			if (trainingPlanPatterns[i]->getName() == name)
				return i;
		}
		return -1;
	}

	void TrainingController::trainingPlanPaused(AbstractTrainingPlan& trainingPlan)
	{
		wxThreadEvent evt(TW_EVT_REFRESH_TP);
		window->GetEventHandler()->QueueEvent(evt.Clone());
		if (saveTrainingPlanAfterPausedIndex != -1 && trainingPlanRepository->getTrainingPlans()[saveTrainingPlanAfterPausedIndex].get() == &trainingPlan)
		{
			wxThreadEvent evtSave(TW_EVT_SAVE_TP);
			evtSave.SetPayload(saveTrainingPlanAfterPausedIndex);
			window->GetEventHandler()->QueueEvent(evtSave.Clone());
			saveTrainingPlanAfterPausedIndex = -1;
		}

		if (saveTrainingSessionAfterPause && allTrainingPlansPaused())
		{
			wxThreadEvent evtSave(TW_EVT_SAVE_TS);
			window->GetEventHandler()->QueueEvent(evtSave.Clone());
			saveTrainingSessionAfterPause = false;
		}
		else if (closeWindowAfterPause && allTrainingPlansPaused())
		{
			window->Close();
		}
	}

	void TrainingController::trainingPlanFinished(AbstractTrainingPlan& trainingPlan)
	{
		if (dynamic_cast<AbstractEvolutionTrainingPlan*>(&trainingPlan))
		{
			const EvolutionLearningResult& learningResult = static_cast<const EvolutionLearningResult&>(static_cast<AbstractEvolutionTrainingPlan&>(trainingPlan).getLearningResult());
			AbstractNeuralNetwork* clone = learningResult.bestObjects.front()->getNeuralNetwork().clone();
			clone->setName("Result of " + trainingPlan.getName());
			neuralNetworkRepository->Add(clone);
		}
		wxThreadEvent evt(TW_EVT_REFRESH_TP);
		window->GetEventHandler()->QueueEvent(evt.Clone());
	}

	void TrainingController::resumeTrainingPlan(AbstractTrainingPlan& trainingPlan)
	{
		trainingPlan.start();
		wxThreadEvent evt(TW_EVT_REFRESH_TP);
		window->GetEventHandler()->QueueEvent(evt.Clone());
	}

	void TrainingController::show()
	{
		window->Show();
	}

	TrainingWindow& TrainingController::getWindow()
	{
		return *window;
	}

	void TrainingController::addSubAppFactory(AbstractSubAppFactory* newSubAppFactory)
	{
		subAppFactories.push_back(newSubAppFactory);
		window->addSubAppFactory(*newSubAppFactory);
	}

	int TrainingController::getIndexOfNeuralNetwork(const AbstractNeuralNetwork& network) const
	{
		return neuralNetworkRepository->getIndexOfNeuralNetwork(network);
	}

	void TrainingController::saveNeuralNetwork(const std::string& path, int neuralNetworkIndex)
	{
		neuralNetworkRepository->save(path, neuralNetworkIndex);
	}

	void TrainingController::loadNeuralNetwork(const std::string& path)
	{
		neuralNetworkRepository->load(path);
	}

	void TrainingController::saveTrainingPlan(int trainingPlanIndex)
	{
		AbstractTrainingPlan* trainingPlan = trainingPlanRepository->getTrainingPlans()[trainingPlanIndex].get();
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

	void TrainingController::saveTrainingPlan(const std::string& path, int trainingPlanIndex)
	{
		trainingPlanRepository->save(path, trainingPlanIndex);
	}

	void TrainingController::loadTrainingPlan(const std::string& path)
	{
		AbstractTrainingPlan& trainingPlan = trainingPlanRepository->load(path);
		trainingPlan.registerObserver(EVT_TP_PAUSED, &TrainingController::trainingPlanPaused, *this);
		trainingPlan.registerObserver(EVT_TP_FINISHED, &TrainingController::trainingPlanFinished, *this);

		if (dynamic_cast<AbstractSingleNNTrainingPlan*>(&trainingPlan))
		{
			neuralNetworkRepository->Add(&static_cast<AbstractSingleNNTrainingPlan&>(trainingPlan).getNeuralNetwork());
		}
	}

	void TrainingController::loadTrainingSession(const std::string& path)
	{
		std::ifstream is(path);
		cereal::XMLInputArchive archive(is);

		archive(*this);

		wxThreadEvent evt(TW_EVT_REFRESH_ALL);
		window->GetEventHandler()->QueueEvent(evt.Clone());
	}

	void TrainingController::saveTrainingSession(const std::string& path)
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
			for (auto trainingPlan = trainingPlanRepository->getTrainingPlans().begin(); trainingPlan != trainingPlanRepository->getTrainingPlans().end(); trainingPlan++)
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


	bool TrainingController::closeWindow()
	{
		if (!allTrainingPlansPaused())
		{
			closeWindowAfterPause = true;
			for (auto trainingPlan = trainingPlanRepository->getTrainingPlans().begin(); trainingPlan != trainingPlanRepository->getTrainingPlans().end(); trainingPlan++)
			{
				if (!(*trainingPlan)->isPaused())
					(*trainingPlan)->pause();
			}
		}
		else
			return true;
	}

	void TrainingController::addSubApp(int subAppFactoryIndex)
	{
		activeSubApps.push_back(std::unique_ptr<AbstractSubApp>(subAppFactories[subAppFactoryIndex]->createSupApp(*this, *window)));
	}

	void TrainingController::openPreferences(int trainingPlanPatternIndex)
	{
		PreferencesController* preferencesController = new PreferencesController(*this, *trainingPlanPatterns[trainingPlanPatternIndex].get(), *window);
		preferencesController->getWindow().Show();
		activeSubApps.push_back(std::unique_ptr<AbstractSubApp>(preferencesController));
	}

	void TrainingController::setTrainingPlanName(int trainingPlanIndex, const std::string& newName)
	{
		trainingPlanRepository->setTrainingPlanName(trainingPlanIndex, newName);
	}

	void TrainingController::removeSubApp(const AbstractSubApp& subApp)
	{
		for (auto activeSubApp = activeSubApps.begin(); activeSubApp != activeSubApps.end(); activeSubApp++)
		{
			if (activeSubApp->get() == &subApp)
			{
				activeSubApps.erase(activeSubApp);
				break;
			}
		}
	}

	bool TrainingController::allTrainingPlansPaused()
	{
		bool allPaused = true;
		for (auto trainingPlan = trainingPlanRepository->getTrainingPlans().begin(); trainingPlan != trainingPlanRepository->getTrainingPlans().end(); trainingPlan++)
		{
			if (!(*trainingPlan)->isPaused())
				allPaused = false;
		}
		return allPaused;
	}

}