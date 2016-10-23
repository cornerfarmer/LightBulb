// Includes
#include "Examples/TicTacToeEvolution/TicTacToe.hpp"
#include "Examples/TicTacToeEvolution/TicTacToeKI.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
//Library includes
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>

using namespace LightBulb;

AbstractEvolutionObject* TicTacToe::createNewObject()
{
	return new TicTacToeKI(*options, *this);
}

TicTacToe::TicTacToe(FeedForwardNetworkTopologyOptions& options_, bool isParasiteWorld_, AbstractCombiningStrategy* combiningStrategy_, AbstractCoevolutionFitnessFunction* fitnessFunction_, AbstractHallOfFameAlgorithm* hallOfFameToAddAlgorithm_, AbstractHallOfFameAlgorithm* hallOfFameToChallengeAlgorithm_)
	: AbstractCoevolutionWorld(isParasiteWorld_, combiningStrategy_, fitnessFunction_, hallOfFameToAddAlgorithm_, hallOfFameToChallengeAlgorithm_)
{
	options.reset(new FeedForwardNetworkTopologyOptions(options_));
	initialize();
}

TicTacToe::TicTacToe()
{
	initialize();
}

void TicTacToe::initialize()
{
	fields.resize(3);
	for (int x = 0; x < fields.size(); x++)
	{
		fields[x].resize(3);
	}
	resetWorld();
	stepMode = false;
}

bool TicTacToe::hasGameFinished()
{
	return (illegalMove || whoHasWon() != 0);
}

int TicTacToe::getFieldValue(int x, int y)
{
	return fields[x][y];
}

int TicTacToe::doCompare(AbstractEvolutionObject& obj1, AbstractEvolutionObject& obj2, int round)
{
	return simulateGame(static_cast<TicTacToeKI&>(obj1), static_cast<TicTacToeKI&>(obj2), round == 1);
}

std::vector<std::vector<int>>& TicTacToe::getFields()
{
	return fields;
}

void TicTacToe::startStepMode()
{
	if (!stepMode)
	{
		stepMode = true;
	}
}

void TicTacToe::stopStepMode()
{
	if (stepMode)
	{
		stepMode = false;
		doNextStep.notify_one();
	}
}

std::vector<std::string> TicTacToe::getDataSetLabels() const
{
	auto labels = AbstractCoevolutionWorld::getDataSetLabels();
	labels.push_back(std::string(parasiteWorld ? DATASET_PARASITE_PREFIX : "") + DATASET_TICTACTOE_RATING);
	return labels;
}

void TicTacToe::nextStep()
{
	if (stepMode)
	{
		doNextStep.notify_all();
	}
}

int TicTacToe::getRoundCount() const
{
	return 2;
}

void TicTacToe::initializeForLearning()
{
}

int TicTacToe::simulateGame(TicTacToeKI& ai1, TicTacToeKI& ai2, bool secondPlayerStarts)
{
	int pointsAI1 = 0;
	int pointsAI2 = 0;
	ai2.resetNN();
	ai1.resetNN();

	ai1.setTicTacToe(*this);
	ai2.setTicTacToe(*this);

	if (secondPlayerStarts == 0)
		startNewGame(1);
	else
		startNewGame(-1);

	int i;
	for (i = 0; i < 9; i++)
	{
		if (stepMode)
		{
			std::unique_lock<std::mutex> doNextStepMutexLock(doNextStepMutex);
			doNextStep.wait(doNextStepMutexLock);
		}
		if (i % 2 == secondPlayerStarts)
		{
			ai1.doNNCalculation();
			if (!illegalMove)
				pointsAI1++;
		}
		else
		{
			ai2.doNNCalculation();
			if (!illegalMove)
				pointsAI2++;
		}

		if (hasGameFinished())
			break;
	}

	if (illegalMove)
	{
		if (currentPlayer == 1)
			return -1;
		else
			return 1;
	}
	else
	{
		int w = whoHasWon();
		if (w == 0) {
			if (parasiteWorld)
				return -1;
			else
				return 1;
		} else if (w == 1) {
			return 1;
		} else if (w == -1) {
			return -1;
		}
	}
}

void TicTacToe::setIllegalMove(bool illegalMove_)
{
	illegalMove = illegalMove_;
}

int TicTacToe::rateKI(AbstractEvolutionObject& rateKI)
{

	int wins = 0;
	int possibleGames = 9 * 7 * 5 * 3;
	possibleGames += 8 * 6 * 4 * 2;

	for (int b = 0; b < 2; b++)
	{
		std::vector<int> decisionNr(b == 0 ? 4 : 4, 0);

		bool decisionCombinationsLeft = true;

		while (decisionCombinationsLeft)
		{
			rateKI.resetNN();
			startNewGame(b == 0 ? -1 : 1);

			int i;
			for (i = 0; i < 9; i++)
			{
				if (i % 2 == 1 - b)
				{
					rateKI.doNNCalculation();
				}
				else
				{
					int x = 0, y = 0;
					int freeFieldNr = -1;
					for (y = 0; y < 3; y++)
					{
						for (x = 0; x < 3; x++)
						{
							if (isFree(x, y))
								freeFieldNr++;
							if ((i == 8 && freeFieldNr == 0) || (i != 8 && freeFieldNr == decisionNr[i / 2]))
								goto setField;
						}
					}
				setField:
					setField(x, y);
				}
				if (hasGameFinished())
					break;
			}

			if ((currentPlayer == -1 && illegalMove) || (whoHasWon() == 1) || i>8)
				wins++;

			decisionCombinationsLeft = !nextDecisionCombination(decisionNr, b);
		}
	}

	log("Best KI: " + std::to_string(wins) + "/" + std::to_string(possibleGames), LL_MEDIUM);
	if (!learningState->disabledDatasets[std::string(parasiteWorld ? DATASET_PARASITE_PREFIX : "") + DATASET_TICTACTOE_RATING])
		learningState->addData(std::string(parasiteWorld ? DATASET_PARASITE_PREFIX : "") + DATASET_TICTACTOE_RATING, (double)wins / possibleGames);

	return wins;
}

bool TicTacToe::nextDecisionCombination(std::vector<int>& decisionNr, int b, int level)
{
	bool changeAtThisLevel = true;
	if (level < 3)
		changeAtThisLevel = nextDecisionCombination(decisionNr, b, level + 1);
	if (changeAtThisLevel) {
		decisionNr[level]++;
		if ((decisionNr[level] >= (4 - level) * 2 + 1 && b == 0) || (decisionNr[level] >= (4 - level) * 2 && b == 1))
		{
			decisionNr[level] = 0;
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

bool TicTacToe::isFree(int x, int y)
{
	return fields[x][y] == 0;
}

void TicTacToe::startNewGame(int firstPlayer)
{
	illegalMove = false;
	resetWorld();
	currentPlayer = firstPlayer;
}

int TicTacToe::whoHasWon()
{
	if (fields[0][0] != 0 && fields[0][0] == fields[0][1] && fields[0][1] == fields[0][2])
		return fields[0][0];
	else if (fields[1][0] != 0 && fields[1][0] == fields[1][1] && fields[1][1] == fields[1][2])
		return fields[1][0];
	else if (fields[2][0] != 0 && fields[2][0] == fields[2][1] && fields[2][1] == fields[2][2])
		return fields[2][0];

	else if (fields[0][0] != 0 && fields[0][0] == fields[1][0] && fields[1][0] == fields[2][0])
		return fields[0][0];
	else if (fields[0][1] != 0 && fields[0][1] == fields[1][1] && fields[1][1] == fields[2][1])
		return fields[0][1];
	else if (fields[0][2] != 0 && fields[0][2] == fields[1][2] && fields[1][2] == fields[2][2])
		return fields[0][2];

	else if (fields[0][0] != 0 && fields[0][0] == fields[1][1] && fields[1][1] == fields[2][2])
		return fields[0][0];
	else if (fields[2][0] != 0 && fields[2][0] == fields[1][1] && fields[1][1] == fields[0][2])
		return fields[2][0];
	else
		return 0;
}

void TicTacToe::setField(int x, int y)
{
	if (!isFree(x, y))
		illegalMove = true;
	else {
		fields[x][y] = currentPlayer;
		currentPlayer *= -1;
		throwEvent(EVT_FIELD_CHANGED, *this);
	}
}


void TicTacToe::resetWorld()
{
	for (auto column = fields.begin(); column != fields.end(); column++)
	{
		for (auto field = column->begin(); field != column->end(); field++)
		{
			*field = 0;
		}
	}
	throwEvent(EVT_FIELD_CHANGED, *this);
}


 void TicTacToe::getSight(std::vector<double>& sight)
{
	sight.resize(18);
	int sightIndex = 0;
	for (auto column = fields.begin(); column != fields.end(); column++)
	{
		for (auto field = column->begin(); field != column->end(); field++)
		{
			int fieldValue = currentPlayer * *field;
			if (fieldValue == 1)
				sight[sightIndex++] = 1;
			else
				sight[sightIndex++] = 0;
			if (fieldValue == -1)
				sight[sightIndex++] = 1;
			else
				sight[sightIndex++] = 0;
		}
	}
}


