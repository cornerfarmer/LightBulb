// Includes
#include "Windows/EvolutionAnalyzerController.hpp"
#include "EvolutionAnalyzerWindow.hpp"
#include <Repositories/TrainingPlanRepository.hpp>
#include "Learning/Evolution/EvolutionLearningRule.hpp"

EvolutionAnalyzerController::EvolutionAnalyzerController(AbstractMainApp* mainApp, TrainingPlanRepository* trainingPlanRepository_, AbstractWindow* parent)
	:AbstractSubApp(mainApp)
{
	selectedTrainingPlan = NULL;
	trainingPlanRepository = trainingPlanRepository_;
	trainingPlanRepository->registerObserver(EVT_TP_CHANGED, &EvolutionAnalyzerController::trainingPlansChanged, this);

	window.reset(new EvolutionAnalyzerWindow(this, parent));

	trainingPlansChanged(trainingPlanRepository);
}

void EvolutionAnalyzerController::prepareClose()
{
	trainingPlanRepository->removeObserver(EVT_TP_CHANGED, &EvolutionAnalyzerController::trainingPlansChanged, this);
	if (selectedTrainingPlan)
		static_cast<EvolutionLearningRule*>(selectedTrainingPlan->getLearningRule())->removeObserver(EVT_EL_EVOLUTIONSTEP, &EvolutionAnalyzerController::evolutionStepCompleted, this);
}

void EvolutionAnalyzerController::trainingPlansChanged(TrainingPlanRepository* trainingPlanRepository)
{
	window->refreshTrainingPlans();
}

std::vector<std::unique_ptr<AbstractTrainingPlan>>* EvolutionAnalyzerController::getTrainingPlans()
{
	return trainingPlanRepository->getTrainingPlans();
}

EvolutionAnalyzerWindow* EvolutionAnalyzerController::getWindow()
{
	return window.get();
}

std::string EvolutionAnalyzerController::getLabel()
{
	return "Evolution highscore";
}

void EvolutionAnalyzerController::selectTrainingPlan(int trainingPlanIndex)
{
	if (selectedTrainingPlan)
		static_cast<EvolutionLearningRule*>(selectedTrainingPlan->getLearningRule())->removeObserver(EVT_EL_EVOLUTIONSTEP, &EvolutionAnalyzerController::evolutionStepCompleted, this);
	selectedTrainingPlan = dynamic_cast<AbstractEvolutionTrainingPlan*>((*trainingPlanRepository->getTrainingPlans())[trainingPlanIndex].get());
	if (selectedTrainingPlan)
		static_cast<EvolutionLearningRule*>(selectedTrainingPlan->getLearningRule())->registerObserver(EVT_EL_EVOLUTIONSTEP, &EvolutionAnalyzerController::evolutionStepCompleted, this);
}

void EvolutionAnalyzerController::evolutionStepCompleted(EvolutionLearningRule* evolutionLearningRule)
{
	currentHighscore = *evolutionLearningRule->getWorld()->getHighscoreList();
	wxThreadEvent evt(EAW_EVT_REFRESH);
	window->GetEventHandler()->QueueEvent(evt.Clone());
}

Highscore* EvolutionAnalyzerController::getCurrentHighscore()
{
	return &currentHighscore;
}
