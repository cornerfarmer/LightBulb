
#pragma once

#ifndef _PONGREINFORCEMENTEXAMPLE_H_
#define _PONGREINFORCEMENTEXAMPLE_H_

#include "LightBulbApp/TrainingPlans/AbstractReinforcementTrainingPlan.hpp"

class PongReinforcementEnvironment;

class PongPolicyGradientExample : public LightBulb::AbstractReinforcementTrainingPlan
{
private:
protected:
	LightBulb::AbstractLearningRule* createLearningRate() override;
	LightBulb::AbstractReinforcementEnvironment* createEnvironment() override;
	LightBulb::AbstractReinforcementIndividual* createIndividual() override;
public:
	PongPolicyGradientExample();
	std::string getOriginalName() const override;
	std::string getDescription() const override;
	AbstractTrainingPlan* createNewFromSameType() const override;
	std::string getLearningRuleName() const override;
};

USE_PARENT_SERIALIZATION_WITHOUT_NAMESPACE(PongPolicyGradientExample, LightBulb::AbstractReinforcementTrainingPlan);

#endif
