// Includes
#include "Windows/AbstractCustomSubApp.hpp"

namespace LightBulb
{
	AbstractCustomSubApp::AbstractCustomSubApp(AbstractMainApp& mainApp, AbstractTrainingPlan& trainingPlan_)
		:AbstractSubApp(mainApp)
	{
		trainingPlan = &trainingPlan_;
	}
}