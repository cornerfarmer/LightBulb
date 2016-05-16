// Includes
#include "Windows/AbstractCustomSubApp.hpp"

AbstractCustomSubApp::AbstractCustomSubApp(AbstractMainApp* mainApp, AbstractTrainingPlan* trainingPlan_)
	:AbstractSubApp(mainApp)
{
	trainingPlan = trainingPlan_;
}
