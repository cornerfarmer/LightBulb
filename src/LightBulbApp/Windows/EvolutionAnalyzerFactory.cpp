// Includes
#include "LightBulbApp/Windows/EvolutionAnalyzerFactory.hpp"
#include "LightBulbApp/Windows/EvolutionAnalyzerController.hpp"
#include "LightBulbApp/Windows/EvolutionAnalyzerWindow.hpp"

namespace LightBulb
{
	EvolutionAnalyzerFactory::EvolutionAnalyzerFactory(TrainingPlanRepository& trainingPlanRepository_)
	{
		trainingPlanRepository = &trainingPlanRepository_;
	}

	AbstractSubApp* EvolutionAnalyzerFactory::createSupApp(AbstractMainApp& mainApp, AbstractWindow& parent) const
	{
		EvolutionAnalyzerController* controller = new EvolutionAnalyzerController(mainApp, *trainingPlanRepository, parent);
		controller->getWindow().Show();
		return controller;
	}

	std::string EvolutionAnalyzerFactory::getLabel() const
	{
		return EvolutionAnalyzerController::getLabel();
	}
}
