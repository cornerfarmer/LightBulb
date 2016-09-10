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
	std::string getDefaultName() override;
	std::string getDescription() override;
	LightBulb::AbstractTrainingPlan* getCopy() override;
	std::string getLearningRuleName() override;
};

USE_PARENT_SERIALIZATION(NatureExample, AbstractEvolutionTrainingPlan);

#endif
