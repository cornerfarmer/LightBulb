// Includes
#include "Examples/MountainCar/MountainCarController.hpp"
// Library includes
#include <TrainingPlans/AbstractTrainingPlan.hpp>
#include "MountainCarDQNExample.hpp"
#include "MountainCarEnvironment.hpp"

using namespace LightBulb;

MountainCarController::MountainCarController(AbstractMainApp& mainApp, AbstractTrainingPlan& trainingPlan_, AbstractWindow& parent)
	:AbstractCustomSubApp(mainApp, trainingPlan_)
{
	environment = static_cast<MountainCarEnvironment*>(&static_cast<MountainCarDQNExample*>(trainingPlan)->getEnvironment());
	window.reset(new MountainCarWindow(*this, parent));
}

void MountainCarController::prepareClose()
{
	stopWatchMode();
}

MountainCarWindow& MountainCarController::getWindow()
{
	return *window.get();
}

void MountainCarController::stopWatchMode()
{
	environment->stopWatchMode();
	environment->removeObserver(EVT_POS_CHANGED, &MountainCarController::posChanged, *this);
}


void MountainCarController::startWatchMode()
{
	environment->startWatchMode();
	environment->registerObserver(EVT_POS_CHANGED, &MountainCarController::posChanged, *this);
}


std::string MountainCarController::getLabel()
{
	return "MountainCar";
}

double MountainCarController::getPosition()
{
	return position;
}

double MountainCarController::getVelocity()
{
	return velocity;
}

int MountainCarController::getAction()
{
	return action;
}

void MountainCarController::posChanged(MountainCarEnvironment& pong)
{
	position = environment->getPosition();
	velocity = environment->getVelocity();
	action = environment->getAction();
	wxThreadEvent evt(MOUNTAINCAR_EVT_POS_CHANGED);
	window->GetEventHandler()->QueueEvent(evt.Clone());
}
