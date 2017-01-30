#pragma once

#ifndef _NETWORKEVOLUTIONEXAMPLE_H_
#define _NETWORKEVOLUTIONEXAMPLE_H_

#include "LightBulbApp/TrainingPlans/AbstractEvolutionTrainingPlan.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"

class NetworkEvolutionExample : public LightBulb::AbstractEvolutionTrainingPlan
{
private:
protected:
	LightBulb::AbstractLearningRule* createLearningRate() override;
	LightBulb::AbstractEvolutionEnvironment* createEnvironment() override;
public:
	NetworkEvolutionExample();
	std::string getOriginalName() const override;
	std::string getDescription() const override;
	AbstractTrainingPlan* createNewFromSameType() const override;
	std::string getLearningRuleName() const override;
};

USE_PARENT_SERIALIZATION_WITHOUT_NAMESPACE(NetworkEvolutionExample, LightBulb::AbstractEvolutionTrainingPlan);

#endif
