#pragma once

#ifndef _FUNCTIONEVOLUTIONEXAMPLE_H_
#define _FUNCTIONEVOLUTIONEXAMPLE_H_

#include "LightBulbApp/TrainingPlans/AbstractEvolutionTrainingPlan.hpp"
#include "LightBulb/LinearAlgebra/Kernel.hpp"

class FunctionEvolutionExample : public LightBulb::AbstractEvolutionTrainingPlan
{
private:
	std::unique_ptr<LightBulb::Kernel> sixHumpCamelFunctionKernel;
protected:
	LightBulb::AbstractLearningRule* createLearningRate() override;
	LightBulb::AbstractEvolutionEnvironment* createEnvironment() override;
public:
	FunctionEvolutionExample();
	void sixHumpCamelFunction(const LightBulb::Vector<>& pos, LightBulb::Scalar<>& value, const LightBulb::CalculatorType& calculatorType);
	std::string getOriginalName() const override;
	std::string getDescription() const override;
	AbstractTrainingPlan* createNewFromSameType() const override;
	std::string getLearningRuleName() const override;
};

USE_PARENT_SERIALIZATION_WITHOUT_NAMESPACE(FunctionEvolutionExample, LightBulb::AbstractEvolutionTrainingPlan);

#endif
