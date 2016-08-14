// Includes
#include "Examples/PongReinforcement/PongReinforcementWorld.hpp"
#include <Learning/LearningState.hpp>

//Library includes

PongReinforcementWorld::PongReinforcementWorld(LayeredNetworkOptions& options_, bool epsilonGreedly, double epsilon)
	: AbstractReinforcementWorld(options_, epsilonGreedly, epsilon)
{
	watchMode = false;
}

double PongReinforcementWorld::doSimulationStep()
{
	if (game.whoHasWon() != 0 || time >= game.getProperties().maxTime || time == -1)
	{
		time = 0;
		game.reset();
	}
	
	game.setPlayer(1);
	doNNCalculation();
	game.setPlayer(-1);
	executeCompareAI();
	game.advanceBall(1);

	if (watchMode)
	{
		throwEvent(EVT_FIELD_CHANGED, this);
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	time++;
	if (game.getState().ballCollidedWithPaddle)
		return 1;
	else
		return game.whoHasWon();
}

void PongReinforcementWorld::getNNInput(std::vector<double>& input)
{
	input.resize(6);
	input[0] = game.getState().ballPosX / game.getProperties().width;
	input[1] = game.getState().ballPosY / game.getProperties().height;
	input[2] = game.getState().ballVelX / game.getProperties().maxBallSpeed;
	input[3] = game.getState().ballVelY / game.getProperties().maxBallSpeed;
	input[4] = game.getState().paddle1Pos / (game.getProperties().height - game.getProperties().paddleHeight);
	input[5] = game.getState().paddle2Pos / (game.getProperties().height - game.getProperties().paddleHeight);
}

void PongReinforcementWorld::interpretNNOutput(std::vector<bool>& output)
{
	if (output[0])
		game.movePaddle(1);
	else if (output[1])
		game.movePaddle(-1);
}


void PongReinforcementWorld::executeCompareAI()
{
	if (game.getState().ballPosY > game.getState().paddle2Pos + game.getProperties().paddleHeight / 2)
		game.movePaddle(1);
	else
		game.movePaddle(-1);
}

void PongReinforcementWorld::initializeForLearning()
{
	AbstractReinforcementWorld::initializeForLearning();
	time = -1;
}


int PongReinforcementWorld::rateKI()
{
	PongGame tmp = game;
	int wins = 0;
	int matchCount = 100;
	for (int i = 0; i < matchCount; i++)
	{
		game.reset();

		double time = 0;
		while (game.whoHasWon() == 0 && time < game.getProperties().maxTime)
		{
			game.setPlayer(1);
			doNNCalculation();
			game.setPlayer(-1);
			executeCompareAI();
			game.advanceBall(1);

			time++;
		}

		if (game.whoHasWon() == 1 || game.whoHasWon() == 0)
			wins++;
	}

	if (!learningState->disabledDatasets[DATASET_PONG_RATING])
		learningState->addData(DATASET_PONG_RATING, (double)wins / matchCount);
	game = tmp;
	return wins;
}


std::vector<std::string> PongReinforcementWorld::getDataSetLabels()
{
	auto labels = AbstractReinforcementWorld::getDataSetLabels();
	labels.push_back(DATASET_PONG_RATING);
	return labels;
}

bool PongReinforcementWorld::isTerminalState()
{
	return game.whoHasWon() != 0 || time >= game.getProperties().maxTime;
}
