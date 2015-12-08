#pragma once

#ifndef _TICTACTOE_H_
#define _TICTACTOE_H_

// Library Includes
#include <vector>
#include <map>
#include <array>
#include <SFML/Graphics.hpp>

// Include
#include "Learning/Evolution/AbstractSimpleEvolutionWorld.hpp"
#include "Examples/TicTacToeDrawer.hpp"
#include "NeuralNetwork/NeuralNetworkIO.hpp"

// Forward declarations
class EvolutionLearningRule;
class AbstractEvolutionObject;
class TicTacToeKI;
class AbstractTile;

class TicTacToe : public AbstractSimpleEvolutionWorld
{
protected:
	std::vector<std::vector<int>> fields;	
	std::map<TicTacToeKI*, double> points;
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
	bool nextDecisionCombination(std::array<int, 4>& decisionNr, int level = 0);
	void simulateGame(TicTacToeKI* ai1, TicTacToeKI* ai2, int startingAI, int& illegalMoves, int& ties);

public:
	TicTacToe();
	void setMaxDistanceShrinkFactor(double maxDistanceShrinkFactor_);
	bool doSimulationStep();
	bool doSimulationStep2();
	void getSight(std::vector<double>& sight);
	void setField(int x, int y);
	double getScore(AbstractEvolutionObject* object);
	bool isFree(int x, int y);
	int getFieldValue(int x, int y);
	int rateKI(TicTacToeKI* rateKI);
	void setIllegalMove(bool illegalMove_);
	std::vector<TicTacToeKI*>* getBestAIs();
	void startNewGame(int firstPlayer);
	bool hasGameFinished();
	void setDebugOutput(bool debugOutput_);
	double getRealScore(AbstractEvolutionObject* object);
	void initializeForLearning();
};

#endif
