// Includes
#include "Examples/PongEvolution/Pong.hpp"
#include "Examples/PongEvolution/PongAI.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
//Library includes
#include <iomanip>
#include <chrono>
#include <thread>

AbstractEvolutionObject* Pong::createNewObject()
{
	return new PongAI(*options, this);
}

Pong::Pong(LayeredNetworkOptions& options_, bool isParasiteWorld_, AbstractCombiningStrategy* combiningStrategy_, AbstractCoevolutionFitnessFunction* fitnessFunction_, AbstractHallOfFameAlgorithm* hallOfFameToAddAlgorithm_, AbstractHallOfFameAlgorithm* hallOfFameToChallengeAlgorithm_)
	: AbstractCoevolutionWorld(isParasiteWorld_, combiningStrategy_, fitnessFunction_, hallOfFameToAddAlgorithm_, hallOfFameToChallengeAlgorithm_)
{
	options.reset(new LayeredNetworkOptions(options_));
	watchMode = false;
}

int Pong::doCompare(AbstractEvolutionObject* obj1, AbstractEvolutionObject* obj2, int round)
{
	return simulateGame(static_cast<PongAI*>(obj1), static_cast<PongAI*>(obj2));
}


std::vector<std::string> Pong::getDataSetLabels()
{
	auto labels = AbstractCoevolutionWorld::getDataSetLabels();
	labels.push_back(std::string(parasiteWorld ? DATASET_PARASITE_PREFIX : "") + DATASET_PONG_RATING);
	return labels;
}


int Pong::getRoundCount()
{
	return 1;
}

void Pong::initializeForLearning()
{
}


void Pong::startWatchMode()
{
	watchMode = true;
}

void Pong::stopWatchMode()
{
	watchMode = false;
}

PongGame* Pong::getGame()
{
	return &game;
}

int Pong::simulateGame(PongAI* ai1, PongAI* ai2)
{
	int pointsAI1 = 0;
	int pointsAI2 = 0;
	ai2->resetNN();
	ai1->resetNN();

	ai1->setPong(this);
	ai2->setPong(this);

	startNewGame();

	double time = 0;
	while (game.whoHasWon() == 0 && time < game.getProperties().maxTime)
	{
		game.setPlayer(1);
		ai1->doNNCalculation();
		game.setPlayer(-1);
		ai2->doNNCalculation();
		game.advanceBall(1);

		/*if (watchMode)
		{
			throwEvent(EVT_FIELD_CHANGED, this);
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
		}*/
		time++;
	}

	if (game.whoHasWon() == 0) {
		if (parasiteWorld)
			return -1;
		else
			return 1;
	}
	else
		return game.whoHasWon();
}

void Pong::executeCompareAI()
{
	if (game.getState().ballPosY > game.getState().paddle2Pos + game.getProperties().paddleHeight / 2)
		game.movePaddle(1);
	else
		game.movePaddle(-1);
}


int Pong::rateKI(AbstractEvolutionObject* rateKI)
{
	int wins = 0;
	int matchCount = 100;
	for (int i = 0; i < matchCount; i++)
	{
		rateKI->resetNN();

		startNewGame();

		double time = 0;
		while (game.whoHasWon() == 0 && time < game.getProperties().maxTime)
		{
			game.setPlayer(1);
			rateKI->doNNCalculation();
			game.setPlayer(-1);
			executeCompareAI();
			game.advanceBall(1);

			if (watchMode)
			{
				throwEvent(EVT_FIELD_CHANGED, this);
				std::this_thread::sleep_for(std::chrono::milliseconds(20));
			}
			time++;
		}

		if (game.whoHasWon() == 1 || game.whoHasWon() == 0)
			wins++;
	}
	log("Best KI: " + std::to_string(wins) + "/" + std::to_string(matchCount), LL_MEDIUM);
	if (!learningState->disabledDatasets[std::string(parasiteWorld ? DATASET_PARASITE_PREFIX : "") + DATASET_PONG_RATING])
		learningState->addData(std::string(parasiteWorld ? DATASET_PARASITE_PREFIX : "") + DATASET_PONG_RATING, (double)wins / matchCount);

	return wins;
}


void Pong::startNewGame()
{
	resetWorld();
}

void Pong::resetWorld()
{
	game.reset();
}

void Pong::getNNInput(std::vector<double>& input)
{
	input.resize(6);
	input[0] = game.getPlayer() * game.getState().ballPosX / game.getProperties().width;
	input[1] = game.getState().ballPosY / game.getProperties().height;
	input[2] = game.getPlayer() * game.getState().ballVelX / game.getProperties().maxBallSpeed;
	input[3] = game.getState().ballVelY / game.getProperties().maxBallSpeed;
	if (game.getPlayer() == 1)
	{
		input[4] = game.getState().paddle1Pos / (game.getProperties().height - game.getProperties().paddleHeight);
		input[5] = game.getState().paddle2Pos / (game.getProperties().height - game.getProperties().paddleHeight);
	}
	else
	{
		input[5] = game.getState().paddle1Pos / (game.getProperties().height - game.getProperties().paddleHeight);
		input[4] = game.getState().paddle2Pos / (game.getProperties().height - game.getProperties().paddleHeight);
	}
}

