// Includes
#include "Windows/PreferencesController.hpp"
#include "TrainingPlans/AbstractTrainingPlan.hpp"

namespace LightBulb
{
	PreferencesController::PreferencesController(AbstractMainApp* mainApp, AbstractTrainingPlan* trainingPlan_, AbstractWindow* parent)
		:AbstractSubApp(mainApp)
	{
		trainingPlan = trainingPlan_;
		window.reset(new PreferencesWindow(this, parent));
	}

	PreferencesWindow* PreferencesController::getWindow()
	{
		return window.get();
	}

	std::string PreferencesController::getLabel()
	{
		return "Preferences";
	}


	std::vector<std::unique_ptr<AbstractPreference>>& PreferencesController::getPreferences()
	{
		return trainingPlan->getPreferences();
	}
}