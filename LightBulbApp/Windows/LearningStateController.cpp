// Includes
#include "Windows/LearningStateController.hpp"
#include <Repositories/NeuralNetworkRepository.hpp>
#include <NetworkTopology/AbstractNetworkTopology.hpp>
#include <ActivationOrder/TopologicalOrder.hpp>
#include <Repositories/TrainingPlanRepository.hpp>

LearningStateController::LearningStateController(TrainingPlanRepository* trainingPlanRepository_, AbstractWindow* parent)
{
	trainingPlanRepository = trainingPlanRepository_;
	trainingPlanRepository->registerObserver(EVT_TP_CHANGED, &LearningStateController::trainingPlansChanged, this);
	window.reset(new LearningStateWindow(this, parent));
}

LearningStateWindow* LearningStateController::getWindow()
{
	return window.get();
}

std::vector<std::unique_ptr<AbstractTrainingPlan>>* LearningStateController::getTrainingPlans()
{
	return trainingPlanRepository->getTrainingPlans();
}

void LearningStateController::trainingPlansChanged(TrainingPlanRepository* trainingPlanRepository)
{
	window->refreshTrainingPlans();
}
