// Includes
#include "Examples/PongEvolution/PongGameController.hpp"
#include "PongEvolutionExample.hpp"
#include "Pong.hpp"
#include <Examples/PongReinforcement/PongPolicyGradientExample.hpp>
#include <Examples/PongReinforcement/PongReinforcementEnvironment.hpp>
#include "LightBulb/Learning/Evolution/AbstractCombiningStrategy.hpp"
#include "LightBulb/Learning/Evolution/AbstractCoevolutionFitnessFunction.hpp"
// Library includes

using namespace LightBulb;

PongGameController::PongGameController(AbstractMainApp& mainApp, AbstractTrainingPlan& trainingPlan_, AbstractWindow& parent)
	:AbstractCustomSubApp(mainApp, trainingPlan_)
{
	if (dynamic_cast<PongEvolutionExample*>(trainingPlan))
		environment = static_cast<Pong*>(&static_cast<PongEvolutionExample*>(trainingPlan)->getEnvironment());
	else
		environment = static_cast<PongReinforcementEnvironment*>(&static_cast<AbstractReinforcementTrainingPlan*>(trainingPlan)->getEnvironment());
	properties = environment->getGame().getProperties();
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
	environment->stopWatchMode();
	environment->removeObserver(EVT_FIELD_CHANGED, &PongGameController::fieldChanged, *this);
}


void PongGameController::startWatchMode()
{
	environment->startWatchMode();
	environment->registerObserver(EVT_FIELD_CHANGED, &PongGameController::fieldChanged, *this);
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

void PongGameController::fieldChanged(AbstractPongEnvironment& pong)
{
	currentState = pong.getGame().getState();
	wxThreadEvent evt(PONG_EVT_FIELD_CHANGED);
	window->GetEventHandler()->QueueEvent(evt.Clone());
}
