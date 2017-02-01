// Includes
#include "LightBulbApp/LightBulbAppPrec.hpp"
#include "LightBulbApp/Windows/PreferencesController.hpp"
#include "LightBulbApp/TrainingPlans/AbstractTrainingPlan.hpp"

namespace LightBulb
{
	PreferencesController::PreferencesController(AbstractMainApp& mainApp, AbstractTrainingPlan& trainingPlan_, AbstractWindow& parent)
		:AbstractSubApp(mainApp)
	{
		trainingPlan = &trainingPlan_;
		window = new PreferencesWindow(*this, parent);
	}

	PreferencesWindow& PreferencesController::getWindow()
	{
		return *window;
	}

	std::string PreferencesController::getLabel()
	{
		return "Preferences";
	}

	const std::vector<std::unique_ptr<AbstractPreferenceElement>>& PreferencesController::getPreferenceGroups()
	{
		return trainingPlan->getPreferenceGroups();
	}

	const AbstractTrainingPlan& PreferencesController::getTrainingPlan()
	{
		return *trainingPlan;
	}
}
