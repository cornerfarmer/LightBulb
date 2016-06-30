// Includes
#include "Examples/PongEvolution/PongGameController.hpp"
// Library includes
#include <exception>
#include <vector>
#include <TrainingPlans/AbstractTrainingPlan.hpp>
#include "PongEvolutionExample.hpp"
#include "Pong.hpp"


PongGameController::PongGameController(AbstractMainApp* mainApp, AbstractTrainingPlan* trainingPlan_, AbstractWindow* parent)
	:AbstractCustomSubApp(mainApp, trainingPlan_)
{
	world = static_cast<Pong*>(static_cast<PongEvolutionExample*>(trainingPlan)->getWorld());
	properties = world->getProperties();
	window.reset(new PongGameWindow(this, parent));
}

void PongGameController::prepareClose()
{
	stopWatchMode();
}

PongGameWindow* PongGameController::getWindow()
{
	return window.get();
}

void PongGameController::stopWatchMode()
{
	world->stopWatchMode();
	world->removeObserver(EVT_FIELD_CHANGED, &PongGameController::fieldChanged, this);
}


void PongGameController::startWatchMode()
{
	world->startWatchMode();
	world->registerObserver(EVT_FIELD_CHANGED, &PongGameController::fieldChanged, this);
}


std::string PongGameController::getLabel()
{
	return "PongGame";
}

PongGameState* PongGameController::getState()
{
	return &currentState;
}

PongGameProperties* PongGameController::getProperties()
{
	return &properties;
}

void PongGameController::fieldChanged(Pong * pong)
{
	currentState = pong->getState();
	wxThreadEvent evt(PONG_EVT_FIELD_CHANGED);
	window->GetEventHandler()->QueueEvent(evt.Clone());
}
