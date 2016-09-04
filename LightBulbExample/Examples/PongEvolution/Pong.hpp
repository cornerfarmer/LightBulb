#pragma once

#ifndef _PONG_H_
#define _PONG_H_

// Library Includes
#include <vector>
#include <map>
#include <array>
#include <mutex>

// Include
#include "Learning/Evolution/AbstractCoevolutionWorld.hpp"
#include "IO/UseParentSerialization.hpp"
#include <NetworkTopology/FeedForwardNetworkTopology.hpp>
#include "PongGame.hpp"
#include "AbstractPongWorld.hpp"

// Forward declarations
class EvolutionLearningRule;
class AbstractEvolutionObject;
class PongAI;
class AbstractTile;

#define DATASET_PONG_RATING "Pong rating"

class Pong : public AbstractCoevolutionWorld, public AbstractPongWorld
{
private:
protected:
	AbstractEvolutionObject* createNewObject() override;
	void resetWorld() override;
	int simulateGame(PongAI* ai1, PongAI* ai2);
	std::unique_ptr<FeedForwardNetworkTopologyOptions> options;
	int doCompare(AbstractEvolutionObject* obj1, AbstractEvolutionObject* obj2, int round) override;
public:
	Pong(FeedForwardNetworkTopologyOptions& options_, bool isParasiteWorld, AbstractCombiningStrategy* combiningStrategy_, AbstractCoevolutionFitnessFunction* fitnessFunction_, AbstractHallOfFameAlgorithm* hallOfFameToAddAlgorithm_ = NULL, AbstractHallOfFameAlgorithm* hallOfFameToChallengeAlgorithm_ = NULL);
	Pong() = default;
	void getNNInput(std::vector<double>& sight);
	void setRandomGenerator(AbstractRandomGenerator* randomGenerator_) override;
	void executeCompareAI();
	int rateKI(AbstractEvolutionObject* rateKI) override;
	void startNewGame();
	void initializeForLearning() override;
	std::vector<std::string> getDataSetLabels() override;
	int getRoundCount() override;
};

USE_EXISTING_PARENT_SERIALIZATION(Pong, AbstractCoevolutionWorld, AbstractEvolutionWorld);

#endif
