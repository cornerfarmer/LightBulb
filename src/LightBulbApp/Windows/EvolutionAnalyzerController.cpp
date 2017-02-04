// Includes
#include "LightBulbApp/Windows/EvolutionAnalyzerController.hpp"
#include "LightBulbApp/Windows/EvolutionAnalyzerWindow.hpp"
#include "LightBulbApp/Repositories/TrainingPlanRepository.hpp"
#include "LightBulb/Learning/Evolution/EvolutionLearningRule.hpp"
#include "LightBulbApp/TrainingPlans/AbstractEvolutionTrainingPlan.hpp"
#include "LightBulb/Learning/Evolution/AbstractEvolutionEnvironment.hpp"
#include "LightBulb/Learning/Evolution/AbstractIndividual.hpp"

namespace LightBulb
{
	EvolutionAnalyzerController::EvolutionAnalyzerController(AbstractMainApp& mainApp, TrainingPlanRepository& trainingPlanRepository_, AbstractWindow& parent)
		:AbstractSubApp(mainApp)
	{
		selectedTrainingPlan = nullptr;
		trainingPlanRepository = &trainingPlanRepository_;
		trainingPlanRepository->registerObserver(EVT_TP_CHANGED, &EvolutionAnalyzerController::trainingPlansChanged, *this);

		window = new EvolutionAnalyzerWindow(*this, parent);

		trainingPlansChanged(*trainingPlanRepository);
	}

	void EvolutionAnalyzerController::prepareClose()
	{
		trainingPlanRepository->removeObserver(EVT_TP_CHANGED, &EvolutionAnalyzerController::trainingPlansChanged, *this);
		if (selectedTrainingPlan)
			static_cast<EvolutionLearningRule&>(selectedTrainingPlan->getLearningRule()).removeObserver(EVT_EL_EVOLUTIONSTEP, &EvolutionAnalyzerController::evolutionStepCompleted, *this);
	}

	void EvolutionAnalyzerController::trainingPlansChanged(TrainingPlanRepository& trainingPlanRepository)
	{
		window->refreshTrainingPlans();
	}

	const std::vector<std::unique_ptr<AbstractTrainingPlan>>& EvolutionAnalyzerController::getTrainingPlans() const
	{
		return trainingPlanRepository->getTrainingPlans();
	}

	EvolutionAnalyzerWindow& EvolutionAnalyzerController::getWindow()
	{
		return *window;
	}

	std::string EvolutionAnalyzerController::getLabel()
	{
		return "Evolution analyzer";
	}

	void EvolutionAnalyzerController::selectTrainingPlan(int trainingPlanIndex)
	{
		if (selectedTrainingPlan)
			static_cast<EvolutionLearningRule&>(selectedTrainingPlan->getLearningRule()).removeObserver(EVT_EL_EVOLUTIONSTEP, &EvolutionAnalyzerController::evolutionStepCompleted, *this);
		selectedTrainingPlan = dynamic_cast<AbstractEvolutionTrainingPlan*>(trainingPlanRepository->getTrainingPlans()[trainingPlanIndex].get());
		if (selectedTrainingPlan)
			static_cast<EvolutionLearningRule&>(selectedTrainingPlan->getLearningRule()).registerObserver(EVT_EL_EVOLUTIONSTEP, &EvolutionAnalyzerController::evolutionStepCompleted, *this);
	}

	void EvolutionAnalyzerController::evolutionStepCompleted(EvolutionLearningRule& evolutionLearningRule)
	{
		auto highscore = evolutionLearningRule.getEnvironment().getHighscoreList();
		currentState.resize(highscore.size());

		int i = 0;
		for (auto entry = highscore.begin(); entry != highscore.end(); entry++, i++)
		{
			currentState[i].first = entry->second->getEvolutionSource();
			currentState[i].second = entry->first;
		}

		wxThreadEvent evt(EAW_EVT_REFRESH);
		window->GetEventHandler()->QueueEvent(evt.Clone());
	}

	const std::vector<std::pair<EvolutionSource, double>>& EvolutionAnalyzerController::getCurrentState() const
	{
		return currentState;
	}
}
