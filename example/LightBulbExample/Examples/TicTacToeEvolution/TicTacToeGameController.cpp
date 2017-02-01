// Includes
#include "Examples/TicTacToeEvolution/TicTacToeGameController.hpp"
// Library includes
#include <vector>
#include "LightBulbApp/TrainingPlans/AbstractTrainingPlan.hpp"
#include "TicTacToeEvolutionExample.hpp"
#include "TicTacToe.hpp"

using namespace LightBulb;

TicTacToeGameController::TicTacToeGameController(AbstractMainApp& mainApp, AbstractTrainingPlan& trainingPlan_, AbstractWindow& parent)
	:AbstractCustomSubApp(mainApp, trainingPlan_)
{
	environment = static_cast<TicTacToe*>(&static_cast<TicTacToeEvolutionExample*>(trainingPlan)->getEnvironment());
	window.reset(new TicTacToeGameWindow(*this, parent));
}

void TicTacToeGameController::prepareClose()
{
	stopStepMode();
}

TicTacToeGameWindow& TicTacToeGameController::getWindow()
{
	return *window.get();
}

void TicTacToeGameController::stopStepMode()
{
	environment->stopStepMode();
	environment->removeObserver(EVT_FIELD_CHANGED, &TicTacToeGameController::fieldsChanged, *this);
}


void TicTacToeGameController::startStepMode()
{
	environment->startStepMode();
	environment->registerObserver(EVT_FIELD_CHANGED, &TicTacToeGameController::fieldsChanged, *this);
}

void TicTacToeGameController::doStep()
{
	environment->nextStep();
}

std::string TicTacToeGameController::getLabel()
{
	return "TicTacToeGame";
}

std::vector<std::vector<int>>& TicTacToeGameController::getFields()
{
	return environment->getFields();
}

void TicTacToeGameController::fieldsChanged(TicTacToe& ticTacToe)
{
	wxThreadEvent evt(TTT_EVT_FIELD_CHANGED);
	window->GetEventHandler()->QueueEvent(evt.Clone());
}
