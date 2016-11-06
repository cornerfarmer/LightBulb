// Includes
#include "Examples/PongEvolution/PongGameController.hpp"
// Library includes
#include <exception>
#include <vector>
#include <TrainingPlans/AbstractTrainingPlan.hpp>
#include "PongEvolutionExample.hpp"
#include "Pong.hpp"
#include <Examples/PongReinforcement/PongPolicyGradientExample.hpp>
#include <Examples/PongReinforcement/PongReinforcementWorld.hpp>

using namespace LightBulb;

PongGameController::PongGameController(AbstractMainApp& mainApp, AbstractTrainingPlan& trainingPlan_, AbstractWindow& parent)
	:AbstractCustomSubApp(mainApp, trainingPlan_)
{
	if (dynamic_cast<PongEvolutionExample*>(trainingPlan))
		world = static_cast<Pong*>(&static_cast<PongEvolutionExample*>(trainingPlan)->getWorld());
	else
		world = &static_cast<PongPolicyGradientExample*>(trainingPlan)->getWorld();
	properties = world->getGame().getProperties();
	window.reset(new PongGameWindow(*this, parent));
}

void PongGameController::prepareClose()
{
	stopWatchMode();
}

PongGameWindow& PongGameController::getWindow()
{
	return *window.get();
}

void PongGameController::stopWatchMode()
{
	world->stopWatchMode();
	world->removeObserver(EVT_FIELD_CHANGED, &PongGameController::fieldChanged, *this);
}


void PongGameController::startWatchMode()
{
	world->startWatchMode();
	world->registerObserver(EVT_FIELD_CHANGED, &PongGameController::fieldChanged, *this);
}


std::string PongGameController::getLabel()
{
	return "PongGame";
}

PongGameState& PongGameController::getState()
{
	return currentState;
}

PongGameProperties& PongGameController::getProperties()
{
	return properties;
}

void PongGameController::fieldChanged(AbstractPongWorld& pong)
{
	currentState = pong.getGame().getState();
	wxThreadEvent evt(PONG_EVT_FIELD_CHANGED);
	window->GetEventHandler()->QueueEvent(evt.Clone());
}
