// Includes
#include "Windows/PreferencesController.hpp"
#include "TrainingPlans/AbstractTrainingPlan.hpp"

PreferencesController::PreferencesController(AbstractTrainingPlan* trainingPlan_, AbstractWindow* parent)
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
