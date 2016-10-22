// Includes
#include "Examples/MountainCar/MountainCarController.hpp"
// Library includes
#include <TrainingPlans/AbstractTrainingPlan.hpp>
#include "MountainCarDQNExample.hpp"
#include "MountainCarWorld.hpp"

using namespace LightBulb;

MountainCarController::MountainCarController(AbstractMainApp& mainApp, AbstractTrainingPlan& trainingPlan_, AbstractWindow& parent)
	:AbstractCustomSubApp(mainApp, trainingPlan_)
{
	world = static_cast<MountainCarWorld*>(&static_cast<MountainCarDQNExample*>(trainingPlan)->getWorld());
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
	world->stopWatchMode();
	world->removeObserver(EVT_POS_CHANGED, &MountainCarController::posChanged, *this);
}


void MountainCarController::startWatchMode()
{
	world->startWatchMode();
	world->registerObserver(EVT_POS_CHANGED, &MountainCarController::posChanged, *this);
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

void MountainCarController::posChanged(MountainCarWorld& pong)
{
	position = world->getPosition();
	velocity = world->getVelocity();
	action = world->getAction();
	wxThreadEvent evt(MOUNTAINCAR_EVT_POS_CHANGED);
	window->GetEventHandler()->QueueEvent(evt.Clone());
}
