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
class PongAI;
class AbstractTile;

#define DATASET_PONG_RATING "Pong rating"

class Pong : public LightBulb::AbstractCoevolutionWorld, public AbstractPongWorld
{
private:
protected:
	LightBulb::AbstractEvolutionObject* createNewObject() override;
	void resetWorld() override;
	int simulateGame(PongAI* ai1, PongAI* ai2);
	std::unique_ptr<LightBulb::FeedForwardNetworkTopologyOptions> options;
	int doCompare(LightBulb::AbstractEvolutionObject* obj1, LightBulb::AbstractEvolutionObject* obj2, int round) override;
public:
	Pong(LightBulb::FeedForwardNetworkTopologyOptions& options_, bool isParasiteWorld, LightBulb::AbstractCombiningStrategy* combiningStrategy_, LightBulb::AbstractCoevolutionFitnessFunction* fitnessFunction_, LightBulb::AbstractHallOfFameAlgorithm* hallOfFameToAddAlgorithm_ = nullptr, LightBulb::AbstractHallOfFameAlgorithm* hallOfFameToChallengeAlgorithm_ = nullptr);
	Pong() = default;
	void getNNInput(std::vector<double>& sight);
	void setRandomGenerator(LightBulb::AbstractRandomGenerator* randomGenerator_) override;
	void executeCompareAI();
	int rateKI(LightBulb::AbstractEvolutionObject* rateKI) override;
	void startNewGame();
	void initializeForLearning() override;
	std::vector<std::string> getDataSetLabels() override;
	int getRoundCount() override;
};

USE_EXISTING_PARENT_SERIALIZATION(Pong, LightBulb::AbstractCoevolutionWorld, LightBulb::AbstractEvolutionWorld);

#endif
