#pragma once

#ifndef _PONG_H_
#define _PONG_H_

// Library Includes
#include <vector>
#include <map>
#include <array>
#include <mutex>

// Include
#include "LightBulb/Learning/Evolution/AbstractCoevolutionEnvironment.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
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
	Pong(LightBulb::FeedForwardNetworkTopologyOptions& options_, bool isParasiteEnvironment, LightBulb::AbstractCombiningStrategy* combiningStrategy_, LightBulb::AbstractCoevolutionFitnessFunction* fitnessFunction_, const std::shared_ptr<LightBulb::AbstractHallOfFameAlgorithm>* hallOfFameToAddAlgorithm_ = nullptr, const std::shared_ptr<LightBulb::AbstractHallOfFameAlgorithm>* hallOfFameToChallengeAlgorithm_ = nullptr);
	Pong() = default;
	void getNNInput(LightBulb::Vector<>& sight);
	void setRandomGenerator(LightBulb::AbstractRandomGenerator& randomGenerator_) override;
	void executeCompareAI();
	int rateIndividual(LightBulb::AbstractIndividual& individual) override;
	void startNewGame();
	std::vector<std::string> getDataSetLabels() const override;
	int getRoundCount() const override;
};

USE_EXISTING_PARENT_SERIALIZATION_WITHOUT_NAMESPACE(Pong, LightBulb::AbstractCoevolutionEnvironment, LightBulb::AbstractEvolutionEnvironment);

#endif
