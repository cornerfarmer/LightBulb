#pragma once

#ifndef _TICTACTOE_H_
#define _TICTACTOE_H_

// Library Includes
#include <vector>
#include <map>
#include <array>
#include <SFML/Graphics.hpp>

// Include
#include "Learning/Evolution/AbstractCoevolutionWorld.hpp"
#include "Examples/TicTacToeDrawer.hpp"
#include "NeuralNetwork/NeuralNetworkIO.hpp"

// Forward declarations
class EvolutionLearningRule;
class AbstractEvolutionObject;
class TicTacToeKI;
class AbstractTile;

class TicTacToe : public AbstractCoevolutionWorld
{
protected:
	std::vector<std::vector<int>> fields;	
	AbstractEvolutionObject* createNewObject();
	sf::RenderWindow window;
	std::unique_ptr<TicTacToeDrawer> drawer;
	void resetWorld();
	int whoHasWon();
	int currentPlayer;
	bool displayMode;
	bool softReset;
	bool illegalMove;
	std::vector<TicTacToeKI*> bestAIs;
	int defaultResetGenerationCount;
	int currentResetGenerationCount;
	double maxDistanceShrinkFactor;
	bool debugOutput;
	int maxDistance;
	int lastBestAICount;
	int generationsSincaLastBestAI;
	double lastBestScore;
	bool nextDecisionCombination(std::vector<int>& decisionNr, int b, int level = 0);
	int simulateGame(TicTacToeKI* ai1, TicTacToeKI* ai2, bool secondPlayerStarts);
	bool tieMode;
	bool printCurrentBestAI;
	int variationStart;
public:
	TicTacToe(AbstractCombiningStrategy* combiningStrategy_, AbstractCoevolutionFitnessFunction* fitnessFunction_, AbstractHallOfFameAlgorithm* hallOfFameAlgorithm_ = NULL);
	void setMaxDistanceShrinkFactor(double maxDistanceShrinkFactor_);
	void getSight(std::vector<double>& sight);
	void setField(int x, int y);
	bool isFree(int x, int y);
	int getFieldValue(int x, int y);
	int rateKI(AbstractEvolutionObject* rateKI);
	void setIllegalMove(bool illegalMove_);
	void startNewGame(int firstPlayer);
	void setDebugOutput(bool debugOutput_);
	void initializeForLearning();
	bool hasGameFinished();
	int compareObjects(AbstractEvolutionObject* obj1, AbstractEvolutionObject* obj2);

};

#endif
