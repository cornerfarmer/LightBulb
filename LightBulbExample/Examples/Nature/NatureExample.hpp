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
	LightBulb::AbstractEvolutionWorld* createWorld() override;
public:
	NatureExample();
	std::string getDefaultName() const override;
	std::string getDescription() const override;
	LightBulb::AbstractTrainingPlan* createNewFromSameType() const override;
	std::string getLearningRuleName() const override;
};

USE_PARENT_SERIALIZATION(NatureExample, AbstractEvolutionTrainingPlan);

#endif
