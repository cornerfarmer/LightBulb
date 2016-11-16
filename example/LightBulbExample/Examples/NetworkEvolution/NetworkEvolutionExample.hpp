#pragma once

#ifndef _NETWORKEVOLUTIONEXAMPLE_H_
#define _NETWORKEVOLUTIONEXAMPLE_H_

#include "TrainingPlans/AbstractEvolutionTrainingPlan.hpp"
#include "IO/UseParentSerialization.hpp"

class NetworkEvolutionExample : public LightBulb::AbstractEvolutionTrainingPlan
{
private:
protected:
	LightBulb::AbstractLearningRule* createLearningRate() override;
	LightBulb::AbstractEvolutionWorld* createWorld() override;
public:
	std::string getOriginalName() const override;
	std::string getDescription() const override;
	AbstractTrainingPlan* createNewFromSameType() const override;
	std::string getLearningRuleName() const override;
};

USE_PARENT_SERIALIZATION(NetworkEvolutionExample, LightBulb::AbstractEvolutionTrainingPlan, );

#endif
