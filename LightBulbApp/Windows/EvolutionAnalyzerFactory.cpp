// Includes
#include "Windows/EvolutionAnalyzerFactory.hpp"
#include "EvolutionAnalyzerController.hpp"

namespace LightBulb
{
	EvolutionAnalyzerFactory::EvolutionAnalyzerFactory(TrainingPlanRepository* trainingPlanRepository_)
	{
		trainingPlanRepository = trainingPlanRepository_;
	}

	AbstractSubApp* EvolutionAnalyzerFactory::createSupApp(AbstractMainApp* mainApp, AbstractWindow* parent)
	{
		EvolutionAnalyzerController* controller = new EvolutionAnalyzerController(mainApp, trainingPlanRepository, parent);
		controller->getWindow()->Show();
		return controller;
	}

	std::string EvolutionAnalyzerFactory::getLabel()
	{
		return EvolutionAnalyzerController::getLabel();
	}
}