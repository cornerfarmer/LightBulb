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

void TicTacToe::doSimulationStep(EvolutionLearningRule& learningRule)
{	
	int ties = 0;
	int firstWon = 0;
	int secondWon = 0;
	int illegalMoves = 0;
	int duplicates = 0;
	static int generationsSincaLastBestAI = 0;
	static double lastBestScore = 0;
	static int lastCompleteNewAI = 0;
	static int duplicatesInARow = 0;
	static int resetsInARow = 0;
	points.clear();
	for (auto ki = objects.begin(); ki != objects.end(); ki++)
	{	
//		for (auto bestAI = bestAIs.begin(); bestAI != bestAIs.end(); bestAI++)
//		{
//			if ((*bestAI)->getNeuralNetwork()->getNetworkTopology()->calculateEuclideanDistance(*(*ki)->getNeuralNetwork()->getNetworkTopology()) < 50)
//			{
//				points[static_cast<TicTacToeKI*>(*ki)] = -30;
//				duplicates++;
//				goto nextKI;
//			}
//		}


		for (int b = 0; b < 2; b++)
		{
			for (auto bestAI = bestAIs.begin() /*+ (bestAIs.size() < 10 ? 0 : bestAIs.size() - 10)*/; bestAI != bestAIs.end(); bestAI++)//intervalAdvance<std::vector<TicTacToeKI*>::iterator>(bestAI, bestAIs.end(), bestAIs.size()/10 + 1))
			{
				simulateGame(static_cast<TicTacToeKI*>(*ki), static_cast<TicTacToeKI*>(*bestAI), b, learningRule, illegalMoves, ties);
			}

			for (auto otherAI = objects.begin(); otherAI != objects.end(); otherAI++)
			{
				if (otherAI != ki)
				{
					simulateGame(static_cast<TicTacToeKI*>(*ki), static_cast<TicTacToeKI*>(*otherAI), b, learningRule, illegalMoves, ties);
				}
			}
		}
		nextKI:;
	}
	//std::cout << "IM:" << illegalMoves << " T:" << ties << " 1W:" << firstWon << " 2W:" << secondWon << " D:" << duplicates << std::endl;

	auto highscore = getHighscoreList();
	if (points[static_cast<TicTacToeKI*>(highscore->front().second)] == 0) {
		TicTacToeKI* newAI = static_cast<TicTacToeKI*>(highscore->front().second->clone(false));
		bool duplicate = false;
		double currentMaxDist = 1000;//1500 * exp(-0.1 * bestAIs.size());
		std::cout << (int)currentMaxDist << std::endl;
		for (int i = 0; i < (int)bestAIs.size(); i++)
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
					std::cout << bestAIs.size() << ",";
					delete(bestAIs[i]);
					bestAIs.erase(bestAIs.begin() + i);
					i = -1;
					std::cout << bestAIs.size() << ",";
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
		std::cout << "Added " << bestAIs.size() << ". best evolution object to bestAI list" << std::endl;
		rateBestKI(learningRule);
		currentResetGenerationCount = std::max((int)(currentResetGenerationCount / 1.1), defaultResetGenerationCount);
		resetsInARow = 0;
	}
	if (lastBestScore != highscore->front().first) {
		generationsSincaLastBestAI = 0;
	} else if (generationsSincaLastBestAI++ > currentResetGenerationCount) {
		generationsSincaLastBestAI = 0;
		currentResetGenerationCount *= 2;
		//objects[0] = highscore->front().second;
		//objects.resize(1);
		std::cout << "Reset" << std::endl;
		if (resetsInARow++ < 1)
			objects.erase(objects.begin(), objects.end() - 1);
		else
			objects.clear();
	}
	lastBestScore = highscore->front().first;
}

void TicTacToe::simulateGame(TicTacToeKI* ai1, TicTacToeKI* ai2, int startingAI, EvolutionLearningRule& learningRule, int& illegalMoves, int& ties)
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
			ai1->doNNCalculation(learningRule);
		}
		else
		{
			ai2->doNNCalculation(learningRule);
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
		//points[static_cast<TicTacToeKI*>(*ki)]-=1;
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

void TicTacToe::rateBestKI(EvolutionLearningRule& learningRule)
{
	TicTacToeKI* bestKI = dynamic_cast<TicTacToeKI*>(bestAIs.back());
	
	int wins = 0;
	int possibleGames = 9 * 7 * 5 * 3;
	std::array<int, 4> decisionNr = {0,0,0,0};

	bool decisionCombinationsLeft = true;

	while (decisionCombinationsLeft)
	{
		bestKI->resetNN();
		startNewGame(-1);
		
		int i;
		for (i = 0; i < 9; i++)
		{
			if (i % 2 == 1)
			{
				bestKI->doNNCalculation(learningRule);
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

	std::cout << "Best KI: " << wins << "/" << possibleGames << std::endl;
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


NeuralNetworkIO<double> TicTacToe::getSight()
{
	static NeuralNetworkIO<double> sight(18);
	int sightIndex = 0;
	for (auto column = fields.begin(); column != fields.end(); column++)
	{
		for (auto field = column->begin(); field != column->end(); field++)
		{
			int fieldValue = currentPlayer * *field;
			if (fieldValue == 1)
				sight.set(0, sightIndex++, 1);
			else
				sight.set(0, sightIndex++, 0);
			if (fieldValue == -1)
				sight.set(0, sightIndex++, 1);
			else
				sight.set(0, sightIndex++, 0);
		}
	}
	return sight;
}

std::vector<TicTacToeKI*>* TicTacToe::getBestAIs()
{
	return &bestAIs;
}

