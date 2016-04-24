// Includes
#include "Examples/TicTacToeEvolution/TicTacToeGameController.hpp"
// Library includes
#include <exception>
#include <vector>
#include <TrainingPlans/AbstractTrainingPlan.hpp>
#include "TicTacToeEvolutionExample.hpp"
#include "TicTacToe.hpp"


TicTacToeGameController::TicTacToeGameController(AbstractTrainingPlan* trainingPlan_, AbstractWindow* parent)
	:AbstractCustomSubApp(trainingPlan_)
{
	world = static_cast<TicTacToe*>(static_cast<TicTacToeEvolutionExample*>(trainingPlan)->getWorld());
	window.reset(new TicTacToeGameWindow(this, parent));
}

TicTacToeGameWindow* TicTacToeGameController::getWindow()
{
	return window.get();
}

void TicTacToeGameController::stopStepMode()
{
	world->stopStepMode();
	world->removeObserver(EVT_FIELD_CHANGED, &TicTacToeGameController::fieldsChanged, this);
}


void TicTacToeGameController::startStepMode()
{
	world->startStepMode();
	world->registerObserver(EVT_FIELD_CHANGED, &TicTacToeGameController::fieldsChanged, this);
}

void TicTacToeGameController::doStep()
{
	world->nextStep();
}

std::string TicTacToeGameController::getLabel()
{
	return "TicTacToeGame";
}

std::vector<std::vector<int>>* TicTacToeGameController::getFields()
{
	return world->getFields();
}

void TicTacToeGameController::fieldsChanged(TicTacToe * ticTacToe)
{
	wxThreadEvent evt(TTT_EVT_FIELD_CHANGED);
	window->GetEventHandler()->QueueEvent(evt.Clone());
}
