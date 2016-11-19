#pragma once

#ifndef _NATUREEXAMPLE_H_
#define _NATUREEXAMPLE_H_

#include "TrainingPlans/AbstractEvolutionTrainingPlan.hpp"
#include "IO/UseParentSerialization.hpp"

class NatureExample : public LightBulb::AbstractEvolutionTrainingPlan
{
private:
protected:
	LightBulb::AbstractLearningRule* createLearningRate() override;
	LightBulb::AbstractEvolutionEnvironment* createEnvironment() override;
public:
	NatureExample();
	std::string getOriginalName() const override;
	std::string getDescription() const override;
	AbstractTrainingPlan* createNewFromSameType() const override;
	std::string getLearningRuleName() const override;
};

USE_PARENT_SERIALIZATION(NatureExample, LightBulb::AbstractEvolutionTrainingPlan, );

#endif
