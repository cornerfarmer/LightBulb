#pragma once

#ifndef _TICTACTOE_H_
#define _TICTACTOE_H_

// Library Includes
#include <vector>
#include <map>
#include <array>
#include <mutex>

// Include
#include "Learning/Evolution/AbstractCoevolutionWorld.hpp"
#include "NeuralNetwork/NeuralNetworkIO.hpp"
#include "IO/UseParentSerialization.hpp"

// Forward declarations
class EvolutionLearningRule;
class AbstractEvolutionObject;
class TicTacToeKI;
class AbstractTile;

enum TicTacToeEvents
{
	EVT_FIELD_CHANGED
};

#define DATASET_TICTACTOE_RATING "TicTacToe rating"

class TicTacToe : public AbstractCoevolutionWorld, public LightBulb::Observable<TicTacToeEvents, TicTacToe>
{
private:
	void initialize();
protected:
	std::vector<std::vector<int>> fields;	
	AbstractEvolutionObject* createNewObject();
	void resetWorld();
	int whoHasWon();
	int currentPlayer;
	bool illegalMove;
	bool nextDecisionCombination(std::vector<int>& decisionNr, int b, int level = 0);
	int simulateGame(TicTacToeKI* ai1, TicTacToeKI* ai2, bool secondPlayerStarts);
	bool stepMode;
	std::condition_variable doNextStep;
	std::mutex doNextStepMutex;
	int doCompare(AbstractEvolutionObject* obj1, AbstractEvolutionObject* obj2, int round);
public:
	TicTacToe(bool isParasiteWorld, AbstractCombiningStrategy* combiningStrategy_, AbstractCoevolutionFitnessFunction* fitnessFunction_, AbstractHallOfFameAlgorithm* hallOfFameToAddAlgorithm_ = NULL, AbstractHallOfFameAlgorithm* hallOfFameToChallengeAlgorithm_ = NULL);
	TicTacToe();
	void getSight(std::vector<double>& sight);
	void setField(int x, int y);
	bool isFree(int x, int y);
	int getFieldValue(int x, int y);
	int rateKI(AbstractEvolutionObject* rateKI);
	void setIllegalMove(bool illegalMove_);
	void startNewGame(int firstPlayer);
	void initializeForLearning();
	bool hasGameFinished();
	std::vector<std::vector<int>>* getFields();
	void startStepMode();
	void stopStepMode();
	std::vector<std::string> getDataSetLabels();
	void nextStep();
	int getRoundCount();
};

USE_PARENT_SERIALIZATION(TicTacToe, AbstractCoevolutionWorld);

#endif
