// Includes
#include "Examples/TicTacToe.hpp"
#include "Examples/TicTacToeKI.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
//Library includes
#include <iostream>
#include <algorithm>
#include <stdexcept>


AbstractEvolutionObject* TicTacToe::createNewObject()
{
	return new TicTacToeKI(this);
}

TicTacToe::TicTacToe()
{
	defaultResetGenerationCount = 32;
	fields.resize(3);
	for (int x = 0; x < fields.size(); x++)
	{
		fields[x].resize(3);
	}
	resetWorld();

	window.create(sf::VideoMode(800, 700), "LightBulb!");
	TicTacToeDrawerOptions options;
	options.ticTacToe = this;
	displayMode = true;
	drawer.reset(new TicTacToeDrawer(options));

	bestAIs.push_back(static_cast<TicTacToeKI*>(createNewObject()));

	currentResetGenerationCount = defaultResetGenerationCount;

	maxDistanceShrinkFactor = 0.9;
	debugOutput = true;
}

int TicTacToe::getFieldValue(int x, int y)
{
	return fields[x][y];
}

template <class Iter>
void intervalAdvance(Iter& it,const Iter& end, int i)
{
	if (it != end -1)
	{
		it += i;
		if (it > end || (it == end && i != 1))
			it = end -1;
	}
	else
		it = end;
}

void TicTacToe::setMaxDistanceShrinkFactor(double maxDistanceShrinkFactor_)
{
	maxDistanceShrinkFactor = maxDistanceShrinkFactor_;
}

void TicTacToe::setDebugOutput(bool debugOutput_)
{
	debugOutput = debugOutput_;
}

bool TicTacToe::doSimulationStep()
{	
	int ties = 0;
	int firstWon = 0;
	int secondWon = 0;
	int illegalMoves = 0;
	int duplicates = 0;

	static int lastCompleteNewAI = 0;
	static int duplicatesInARow = 0;
	static int resetsInARow = 0;

	points.clear();
	for (auto ki = objects.begin(); ki != objects.end(); ki++)
	{	
		for (auto bestAI = bestAIs.begin(); bestAI != bestAIs.end(); bestAI++)
		{
			double distance = (*bestAI)->getNeuralNetwork()->getNetworkTopology()->calculateEuclideanDistance(*(*ki)->getNeuralNetwork()->getNetworkTopology());
			if (distance < maxDistance)
			{
				points[static_cast<TicTacToeKI*>(*ki)] = -800 * maxDistance / distance;
				duplicates++;
				goto nextKI;
			}
		}


		for (int b = 0; b < 2; b++)
		{
			for (auto bestAI = bestAIs.begin() /*+ (bestAIs.size() < 10 ? 0 : bestAIs.size() - 10)*/; bestAI != bestAIs.end(); bestAI++)//intervalAdvance<std::vector<TicTacToeKI*>::iterator>(bestAI, bestAIs.end(), bestAIs.size()/10 + 1))
			{
				simulateGame(static_cast<TicTacToeKI*>(*ki), static_cast<TicTacToeKI*>(*bestAI), b, illegalMoves, ties);
			}

//			for (auto otherAI = objects.begin(); otherAI != objects.end(); otherAI++)
//			{
//				if (otherAI != ki)
//				{
//					simulateGame(static_cast<TicTacToeKI*>(*ki), static_cast<TicTacToeKI*>(*otherAI), b, learningRule, illegalMoves, ties);
//				}
//			}
		}
		nextKI:;
	}
	//std::cout << "IM:" << illegalMoves << " T:" << ties << " 1W:" << firstWon << " 2W:" << secondWon << " D:" << duplicates << std::endl;

	auto highscore = getHighscoreList();
	if (points[static_cast<TicTacToeKI*>(highscore->front().second)] == 0) {
		TicTacToeKI* newAI = static_cast<TicTacToeKI*>(highscore->front().second->clone(false));
		bool duplicate = false;
		double currentMaxDist = maxDistance / maxDistanceShrinkFactor;//1500 * exp(-0.1 * bestAIs.size());

		for (int i = 0; i < lastBestAICount; i++)
		{
			if (bestAIs[i]->getNeuralNetwork()->getNetworkTopology()->calculateEuclideanDistance(*newAI->getNeuralNetwork()->getNetworkTopology()) < currentMaxDist)
			{
//				if (i < lastCompleteNewAI || duplicatesInARow < 20)
//				{
//					duplicatesInARow++;
//					if (i >= lastCompleteNewAI)
//					{
//						duplicate = true;
//					}
					delete(bestAIs[i]);
					bestAIs.erase(bestAIs.begin() + i);
					lastBestAICount--;
					i = -1;
					if (debugOutput)
						std::cout << "Found a similar AI" << std::endl;
					//break;
//				}
//				else
//				{
//					duplicate = true;
//					if (duplicatesInARow >= 20)
//						duplicatesInARow = 0;
//				}
			}
		}


		if (!duplicate)
		{
			lastCompleteNewAI = bestAIs.size();
			duplicatesInARow = 0;
		}
		bestAIs.push_back(newAI);
		if (debugOutput)
			std::cout << "Added " << bestAIs.size() << ". best evolution object to bestAI list" << std::endl;
		rateKI(dynamic_cast<TicTacToeKI*>(bestAIs.back()));
		//currentResetGenerationCount = std::max((int)(currentResetGenerationCount / 1.1), defaultResetGenerationCount);
		generationsSincaLastBestAI = 0;
		resetsInARow = 0;
	}
	if (lastBestScore != highscore->front().first) {
		generationsSincaLastBestAI = 0;
	} else if (generationsSincaLastBestAI++ > currentResetGenerationCount) {
		if (!softReset)
		{
			currentResetGenerationCount *= 1.05;
			maxDistance *= 0.9;
			std::cout << "Switched to the next mode: d: " << maxDistance << " r: " << currentResetGenerationCount << std::endl;
			//objects[0] = highscore->front().second;
			//objects.resize(1);
			std::cout << "Hard Reset" << std::endl;

			objects.clear();
			for (auto bestAI = bestAIs.begin() + lastBestAICount; bestAI != bestAIs.end(); bestAI++)
			{
				objects.push_back((*bestAI)->clone(false));
			}
			lastBestAICount = bestAIs.size();
			softReset = true;
		}
		else
		{
			std::cout << "Soft Reset" << std::endl;
			objects.clear();
			softReset = false;
		}
		return true;
	}
	lastBestScore = highscore->front().first;
	return false;
}

double TicTacToe::getRealScore(AbstractEvolutionObject* object)
{
	return rateKI(static_cast<TicTacToeKI*>(object));
}

void TicTacToe::initializeForLearning()
{
	bestAIs.clear();
	maxDistance = 10000;
	lastBestAICount = 0;
	generationsSincaLastBestAI = 0;
	lastBestScore = 0;
	softReset = true;
}

void TicTacToe::simulateGame(TicTacToeKI* ai1, TicTacToeKI* ai2, int startingAI, int& illegalMoves, int& ties)
{
	ai2->resetNN();
	ai1->resetNN();

	if (startingAI == 0)
		startNewGame(1);
	else
		startNewGame(-1);

	int i;
	for (i = 0; i < 9; i++)
	{
		if (i % 2 == startingAI)
		{
			ai1->doNNCalculation();
		}
		else
		{
			ai2->doNNCalculation();
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed)
				displayMode = !displayMode;
		}

		if (displayMode && window.isOpen()) {
			window.clear();
			drawer->recalculateAllValues();
			drawer->draw(window);
			window.display();
		}

		if (illegalMove)
			break;
	}
	//if (whoHasWon() == 1)
	//	points[static_cast<TicTacToeKI*>(*ki)]++;
	if (illegalMove)
	{
		if (currentPlayer == 1) {
			points[ai1]-=10-i;
			illegalMoves++;
		}
	}
	else
	{
		// TODO: discuss if this makes sense:
		//points[ai1]-=1;
		ties++;
	}/*
	else if (whoHasWon() == 1)
	{
		points[static_cast<TicTacToeKI*>(*ki)] += 1;
		points[static_cast<TicTacToeKI*>(*otherKI)] -= 1;
		firstWon++;
	}
	else if (whoHasWon() == -1)
	{
		points[static_cast<TicTacToeKI*>(*otherKI)] += 1;
		points[static_cast<TicTacToeKI*>(*ki)] -= 1;
		secondWon++;
	}*/
}

void TicTacToe::setIllegalMove(bool illegalMove_)
{
	illegalMove = illegalMove_;
}

int TicTacToe::rateKI(TicTacToeKI* rateKI)
{
	//TicTacToeKI* bestKI = dynamic_cast<TicTacToeKI*>(bestAIs.back());
	
	int wins = 0;
	int possibleGames = 9 * 7 * 5 * 3;
	std::array<int, 4> decisionNr = {0,0,0,0};

	bool decisionCombinationsLeft = true;

	while (decisionCombinationsLeft)
	{
		rateKI->resetNN();
		startNewGame(-1);
		
		int i;
		for (i = 0; i < 9; i++)
		{
			if (i % 2 == 1)
			{
				rateKI->doNNCalculation();
			}
			else
			{ 
				int x, y;
				int freeFieldNr = -1;
				for (y = 0; y < 3; y++)
				{
					for (x = 0; x < 3; x++)
					{
						if (isFree(x, y))
							freeFieldNr++;
						if ((i == 8 && freeFieldNr == 0) || (i!=8 &&freeFieldNr == decisionNr[i / 2]))
							goto setField;
					}
				}
			setField:
				setField(x, y);
			}
			if (illegalMove)
				break;
		}

		if (currentPlayer == -1 || i > 8)
			wins++;

		decisionCombinationsLeft = !nextDecisionCombination(decisionNr);
	}

	if (debugOutput)
		std::cout << "Best KI: " << wins << "/" << possibleGames << std::endl;
	return wins;
}

bool TicTacToe::nextDecisionCombination(std::array<int, 4>& decisionNr, int level)
{
	bool changeAtThisLevel = true;
	if (level < 3)
		changeAtThisLevel = nextDecisionCombination(decisionNr, level + 1);
	if (changeAtThisLevel) {
		decisionNr[level]++;
		if (decisionNr[level] >= (4 - level) * 2 + 1)
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

bool TicTacToe::hasGameFinished()
{
	return (illegalMove);// || whoHasWon() != 0);
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
	}
}

double TicTacToe::getScore(AbstractEvolutionObject* object)
{
	return points[static_cast<TicTacToeKI*>(object)];
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

std::vector<TicTacToeKI*>* TicTacToe::getBestAIs()
{
	return &bestAIs;
}

