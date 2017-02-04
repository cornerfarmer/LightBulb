#pragma once

#ifndef _TICTACTOE_H_
#define _TICTACTOE_H_

// Library Includes
#include <vector>
#include <array>
#include <mutex>
#include <condition_variable>

// Include
#include "LightBulb/Learning/Evolution/AbstractCoevolutionEnvironment.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"

// Forward declarations
class TicTacToeAI;
class AbstractTile;

enum TicTacToeEvents : unsigned int
{
	EVT_FIELD_CHANGED
};

#define DATASET_TICTACTOE_RATING "TicTacToe rating"

class TicTacToe : public LightBulb::AbstractCoevolutionEnvironment, public LightBulb::Observable<TicTacToeEvents, TicTacToe>
{
private:
	void initialize();
protected:
	std::vector<std::vector<int>> fields;
	LightBulb::AbstractIndividual* createNewIndividual() override;
	void resetEnvironment() override;
	int whoHasWon();
	int currentPlayer;
	bool illegalMove;
	bool nextDecisionCombination(std::vector<int>& decisionNr, int b, int level = 0);
	int simulateGame(TicTacToeAI& ai1, TicTacToeAI& ai2, bool secondPlayerStarts);
	bool stepMode;
	std::condition_variable doNextStep;
	std::mutex doNextStepMutex;
	std::unique_ptr<LightBulb::FeedForwardNetworkTopologyOptions> options;
	int doCompare(LightBulb::AbstractIndividual& obj1, LightBulb::AbstractIndividual& obj2, int round) override;
public:
	TicTacToe(LightBulb::FeedForwardNetworkTopologyOptions& options_, bool isParasiteEnvironment, LightBulb::AbstractCombiningStrategy* combiningStrategy_, LightBulb::AbstractCoevolutionFitnessFunction* fitnessFunction_, const std::shared_ptr<LightBulb::AbstractHallOfFameAlgorithm>* hallOfFameToAddAlgorithm_ = nullptr, const std::shared_ptr<LightBulb::AbstractHallOfFameAlgorithm>* hallOfFameToChallengeAlgorithm_ = nullptr);
	TicTacToe();
	void getSight(LightBulb::Vector<>& sight);
	void setField(int x, int y);
	bool isFree(int x, int y);
	int getFieldValue(int x, int y);
	int rateIndividual(LightBulb::AbstractIndividual& rateKI) override;
	void setIllegalMove(bool illegalMove_);
	void startNewGame(int firstPlayer);
	void initializeForLearning() override;
	bool hasGameFinished();
	std::vector<std::vector<int>>& getFields();
	void startStepMode();
	void stopStepMode();
	std::vector<std::string> getDataSetLabels() const override;
	void nextStep();
	int getRoundCount() const override;
};

USE_EXISTING_PARENT_SERIALIZATION_WITHOUT_NAMESPACE(TicTacToe, LightBulb::AbstractCoevolutionEnvironment, LightBulb::AbstractEvolutionEnvironment);

#endif
