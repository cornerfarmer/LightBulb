#pragma once

#ifndef _PONG_H_
#define _PONG_H_

// Library Includes
#include <vector>
#include <map>
#include <array>
#include <mutex>

// Include
#include "Learning/Evolution/AbstractCoevolutionEnvironment.hpp"
#include "IO/UseParentSerialization.hpp"
#include <NetworkTopology/FeedForwardNetworkTopology.hpp>
#include "PongGame.hpp"
#include "AbstractPongEnvironment.hpp"

// Forward declarations
class PongAI;
class AbstractTile;

#define DATASET_PONG_RATING "Pong rating"

class Pong : public LightBulb::AbstractCoevolutionEnvironment, public AbstractPongEnvironment
{
private:
protected:
	LightBulb::AbstractIndividual* createNewIndividual() override;
	void resetEnvironment() override;
	int simulateGame(PongAI& ai1, PongAI& ai2);
	std::unique_ptr<LightBulb::FeedForwardNetworkTopologyOptions> options;
	int doCompare(LightBulb::AbstractIndividual& obj1, LightBulb::AbstractIndividual& obj2, int round) override;
public:
	Pong(LightBulb::FeedForwardNetworkTopologyOptions& options_, bool isParasiteEnvironment, LightBulb::AbstractCombiningStrategy* combiningStrategy_, LightBulb::AbstractCoevolutionFitnessFunction* fitnessFunction_, LightBulb::AbstractHallOfFameAlgorithm* hallOfFameToAddAlgorithm_ = nullptr, LightBulb::AbstractHallOfFameAlgorithm* hallOfFameToChallengeAlgorithm_ = nullptr);
	Pong() = default;
	void getNNInput(std::vector<double>& sight);
	void setRandomGenerator(LightBulb::AbstractRandomGenerator& randomGenerator_) override;
	void executeCompareAI();
	int rateIndividual(LightBulb::AbstractIndividual& rateKI) override;
	void startNewGame();
	void initializeForLearning() override;
	std::vector<std::string> getDataSetLabels() const override;
	int getRoundCount() const override;
};

USE_EXISTING_PARENT_SERIALIZATION(Pong, LightBulb::AbstractCoevolutionEnvironment, LightBulb::AbstractEvolutionEnvironment, );

#endif
