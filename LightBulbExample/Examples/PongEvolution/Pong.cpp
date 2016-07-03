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
	initialize();
}

void Pong::initialize()
{
	watchMode = false;
	properties.minBallSpeed = 2;
	properties.width = 210;
	properties.height = 160;
	properties.ballRad = 5;
	properties.paddleSpeed = 5;
	properties.paddleHeight = 30;
	properties.paddleWidth = 10;
	properties.maxTime = 1000; // 1000
	properties.speedIncreaseFac = 1.2; // 1.2
	properties.maxBallSpeed = properties.width / ((double)(properties.height - properties.paddleHeight) / properties.paddleSpeed);
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

void Pong::movePaddle(int dir)
{
	if (currentPlayer == 1)
	{
		if (dir == 1)
			state.paddle1Pos += properties.paddleSpeed;
		else if(dir == -1)
			state.paddle1Pos -= properties.paddleSpeed;
		state.paddle1Pos = std::max(0.0, std::min((double)(properties.height - properties.paddleHeight), state.paddle1Pos));
	}
	else
	{
		if (dir == 1)
			state.paddle2Pos += properties.paddleSpeed;
		else if (dir == -1)
			state.paddle2Pos -= properties.paddleSpeed;
		state.paddle2Pos = std::max(0.0, std::min((double)(properties.height - properties.paddleHeight), state.paddle2Pos));
	}
}


void Pong::startWatchMode()
{
	watchMode = true;
}

void Pong::stopWatchMode()
{
	watchMode = false;
}

PongGameState Pong::getState()
{
	return state;
}

PongGameProperties Pong::getProperties()
{
	return properties;
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
	while (whoHasWon() == 0 && time < properties.maxTime)
	{
		currentPlayer = 1;
		ai1->doNNCalculation();
		currentPlayer = -1;
		ai2->doNNCalculation();
		advanceBall(1);

		/*if (watchMode)
		{
			throwEvent(EVT_FIELD_CHANGED, this);
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
		}*/
		time++;
	}

	if (whoHasWon() == 0) {
		if (parasiteWorld)
			return -1;
		else
			return 1;
	}
	else
		return whoHasWon();
}

void Pong::executeCompareAI()
{
	if (state.ballPosY > state.paddle2Pos + properties.paddleHeight / 2)
		movePaddle(1);
	else
		movePaddle(-1);
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
		while (whoHasWon() == 0 && time < properties.maxTime)
		{
			currentPlayer = 1;
			rateKI->doNNCalculation();
			currentPlayer = -1;
			executeCompareAI();
			advanceBall(1);

			if (watchMode)
			{
				throwEvent(EVT_FIELD_CHANGED, this);
				std::this_thread::sleep_for(std::chrono::milliseconds(20));
			}
			time++;
		}

		if (whoHasWon() == 1 || whoHasWon() == 0)
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

int Pong::whoHasWon()
{
	if (state.ballPosX + properties.ballRad >= properties.width)
		return -1;
	else if (state.ballPosX <= 0)
		return 1;
	else
		return 0;
}

void Pong::advanceBall(double fac)
{
	double nextBallPosX = state.ballPosX + state.ballVelX * fac;
	double nextBallPosY = state.ballPosY + state.ballVelY * fac;

	double colTimeX = 0, colTimeY = 0;

	if (nextBallPosY <= 0)
		colTimeY = state.ballPosY / -state.ballVelY;

	if (nextBallPosY + properties.ballRad >= properties.height)
		colTimeY = (properties.height - (state.ballPosY + properties.ballRad)) / state.ballVelY;

	if (nextBallPosX <= 0)
		colTimeX = state.ballPosX / -state.ballVelX;

	if (nextBallPosX + properties.ballRad >= properties.width)
		colTimeX = (properties.width - (state.ballPosX + properties.ballRad)) / state.ballVelX;

	if (colTimeX > 0 && (colTimeY == 0 || colTimeX <= colTimeY))
	{
		advanceBallWithoutCollision(colTimeX);
		if ((state.ballVelX > 0 && state.ballPosY + properties.ballRad >= state.paddle1Pos && state.ballPosY <= state.paddle1Pos + properties.paddleHeight) ||
			(state.ballVelX < 0 && state.ballPosY + properties.ballRad >= state.paddle2Pos && state.ballPosY <= state.paddle2Pos + properties.paddleHeight))
		{
			state.ballVelX *= -1;
			advanceBall(fac - colTimeX);
			if (std::abs(state.ballVelX * properties.speedIncreaseFac) < properties.maxBallSpeed && std::abs(state.ballVelY * properties.speedIncreaseFac) < properties.maxBallSpeed) {
				state.ballVelX *= properties.speedIncreaseFac;
				state.ballVelY *= properties.speedIncreaseFac;
			}
		}
		else
		{
			advanceBallWithoutCollision(fac - colTimeX);
		}
	}
	else if (colTimeY > 0)
	{
		advanceBallWithoutCollision(colTimeY);
		state.ballVelY *= -1;
		advanceBall(fac - colTimeY);
	}
	else
		advanceBallWithoutCollision(fac);
}

void Pong::advanceBallWithoutCollision(double fac)
{
	state.ballPosX += state.ballVelX * fac;
	state.ballPosY += state.ballVelY * fac;
}

void Pong::resetWorld()
{
	state.ballPosX = properties.width / 2;
	state.ballPosY = properties.height / 2;

	state.ballVelX = (double)rand() / RAND_MAX * (properties.maxBallSpeed - properties.minBallSpeed) / 8.0 + properties.minBallSpeed;
	if (rand() > RAND_MAX / 2)
		state.ballVelX *= -1;

	state.ballVelY = (double)rand() / RAND_MAX * (properties.maxBallSpeed - properties.minBallSpeed) / 8.0 + properties.minBallSpeed;
	if (rand() > RAND_MAX / 2)
		state.ballVelY *= -1;

	state.paddle1Pos = properties.height / 2;
	state.paddle2Pos = properties.height / 2;
}


 void Pong::getNNInput(std::vector<double>& input)
{
	 input.resize(6);
	 input[0] = currentPlayer * state.ballPosX / properties.width;
	 input[1] = state.ballPosY / properties.height;
	 input[2] = currentPlayer * state.ballVelX / properties.maxBallSpeed;
	 input[3] = state.ballVelY / properties.maxBallSpeed;
	 if (currentPlayer == 1) 
	 {
		 input[4] = state.paddle1Pos / (properties.height - properties.paddleHeight);
		 input[5] = state.paddle2Pos / (properties.height - properties.paddleHeight);
	 }
	 else
	 {
		 input[5] = state.paddle1Pos / (properties.height - properties.paddleHeight);
		 input[4] = state.paddle2Pos / (properties.height - properties.paddleHeight);
	 }
}
