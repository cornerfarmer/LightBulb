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

	const std::string& PreferencesController::getLabel()
	{
		return "Preferences";
	}


	const std::vector<std::unique_ptr<AbstractPreferenceElement>>& PreferencesController::getPreferenceGroups()
	{
		return trainingPlan->getPreferenceGroups();
	}
}