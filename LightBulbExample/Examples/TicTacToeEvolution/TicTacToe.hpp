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
#include <NetworkTopology/FeedForwardNetworkTopology.hpp>

// Forward declarations
class TicTacToeKI;
class AbstractTile;

enum TicTacToeEvents
{
	EVT_FIELD_CHANGED
};

#define DATASET_TICTACTOE_RATING "TicTacToe rating"

class TicTacToe : public LightBulb::AbstractCoevolutionWorld, public LightBulb::Observable<TicTacToeEvents, TicTacToe>
{
private:
	void initialize();
protected:
	std::vector<std::vector<int>> fields;	
	LightBulb::AbstractEvolutionObject* createNewObject() override;
	void resetWorld() override;
	int whoHasWon();
	int currentPlayer;
	bool illegalMove;
	bool nextDecisionCombination(std::vector<int>& decisionNr, int b, int level = 0);
	int simulateGame(TicTacToeKI* ai1, TicTacToeKI* ai2, bool secondPlayerStarts);
	bool stepMode;
	std::condition_variable doNextStep;
	std::mutex doNextStepMutex;
	std::unique_ptr<LightBulb::FeedForwardNetworkTopologyOptions> options;
	int doCompare(LightBulb::AbstractEvolutionObject* obj1, LightBulb::AbstractEvolutionObject* obj2, int round) override;
public:
	TicTacToe(LightBulb::FeedForwardNetworkTopologyOptions& options_, bool isParasiteWorld, LightBulb::AbstractCombiningStrategy* combiningStrategy_, LightBulb::AbstractCoevolutionFitnessFunction* fitnessFunction_, LightBulb::AbstractHallOfFameAlgorithm* hallOfFameToAddAlgorithm_ = NULL, LightBulb::AbstractHallOfFameAlgorithm* hallOfFameToChallengeAlgorithm_ = NULL);
	TicTacToe();
	void getSight(std::vector<double>& sight);
	void setField(int x, int y);
	bool isFree(int x, int y);
	int getFieldValue(int x, int y);
	int rateKI(LightBulb::AbstractEvolutionObject* rateKI) override;
	void setIllegalMove(bool illegalMove_);
	void startNewGame(int firstPlayer);
	void initializeForLearning() override;
	bool hasGameFinished();
	std::vector<std::vector<int>>* getFields();
	void startStepMode();
	void stopStepMode();
	std::vector<std::string> getDataSetLabels() override;
	void nextStep();
	int getRoundCount() override;
};

USE_EXISTING_PARENT_SERIALIZATION(TicTacToe, LightBulb::AbstractCoevolutionWorld, LightBulb::AbstractEvolutionWorld);

#endif
