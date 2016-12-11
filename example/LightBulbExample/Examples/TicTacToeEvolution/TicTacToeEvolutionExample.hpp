
#pragma once

#ifndef _TICTACTOEEVOLUTIONEXAMPLE_H_
#define _TICTACTOEEVOLUTIONEXAMPLE_H_

#include "LightBulbApp/TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"
#include "LightBulb/Learning/Evolution/SharedSamplingCombiningStrategy.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/Learning/Evolution/AbstractHallOfFameAlgorithm.hpp"

class TicTacToe;

class TicTacToeEvolutionExample : public LightBulb::AbstractCoevolutionTrainingPlan
{
private:
	std::shared_ptr<LightBulb::AbstractHallOfFameAlgorithm> hof1;
	std::shared_ptr<LightBulb::AbstractHallOfFameAlgorithm> hof2;
	LightBulb::SharedSamplingCombiningStrategy* cs1;
	LightBulb::SharedSamplingCombiningStrategy* cs2;
protected:
	LightBulb::AbstractLearningRule* createLearningRate() override;
	LightBulb::FeedForwardNetworkTopologyOptions getNetworkOptions();
	LightBulb::AbstractEvolutionEnvironment* createEnvironment() override;
	LightBulb::AbstractEvolutionEnvironment* createParasiteEnvironment() override;
public:
	TicTacToeEvolutionExample();
	std::string getOriginalName() const override;
	std::string getDescription() const override;
	AbstractTrainingPlan* createNewFromSameType() const override;
	std::string getLearningRuleName() const override;
};

USE_PARENT_SERIALIZATION_WITHOUT_NAMESPACE(TicTacToeEvolutionExample, LightBulb::AbstractCoevolutionTrainingPlan);

#endif
