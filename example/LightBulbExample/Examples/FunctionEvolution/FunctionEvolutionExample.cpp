#include "FunctionEvolutionExample.hpp"
#include <Learning/Evolution/EvolutionLearningRule.hpp>
#include <Learning/Evolution/ConstantCreationCommand.hpp>
#include <Learning/Evolution/EvolutionStrategy/RecombinationAlgorithm.hpp>
#include <Learning/Evolution/EvolutionStrategy/MutationAlgorithm.hpp>
#include <Learning/Evolution/ConstantRecombinationCommand.hpp>
#include <Learning/Evolution/ConstantMutationCommand.hpp>
#include <Learning/Evolution/BestSelectionCommand.hpp>
#include <Learning/Evolution/StochasticUniversalSamplingSelector.hpp>
#include <Learning/Evolution/ConstantReuseCommand.hpp>
#include <Learning/Evolution/RateDifferenceCondition.hpp>
#include <Examples/FunctionEvolution/FunctionSimulator.hpp>
#include <Learning/Evolution/BestReuseSelector.hpp>
#include <Learning/Evolution/ScoreCondition.hpp>

using namespace LightBulb;

static double sixHumpCamelFunction(std::vector<float> pos)
{
	return -1 * (4 * pow(pos[0], 2) - 2.1 * pow(pos[0], 4) + pow(pos[0], 6) / 3 + pos[0] * pos[1] - 4 * pow(pos[1], 2) + 4 * pow(pos[1], 4));
}

AbstractLearningRule* FunctionEvolutionExample::createLearningRate()
{
	

	EvolutionLearningRuleOptions options;
	RateDifferenceCondition* rateDifferenceCondition = new RateDifferenceCondition(0.00001, 10);
	options.exitConditions.push_back(rateDifferenceCondition);
	options.exitConditions.push_back(new ScoreCondition(1.031627 + 10000));
	ConstantCreationCommand* constantCreationCommand = new ConstantCreationCommand(20);
	options.creationCommands.push_back(constantCreationCommand);
	options.reuseCommands.push_back(new ConstantReuseCommand(new BestReuseSelector(), 1));
	BestSelectionCommand* bestSelectionCommand = new BestSelectionCommand(20);
	options.selectionCommands.push_back(bestSelectionCommand);
	MutationAlgorithm* mutationAlgorithm = new MutationAlgorithm(1.6);
	ConstantMutationCommand* constantMutationCommand = new ConstantMutationCommand(mutationAlgorithm, new StochasticUniversalSamplingSelector(), 1.8);
	options.mutationsCommands.push_back(constantMutationCommand);
	ConstantRecombinationCommand* constantRecombinationCommand = new ConstantRecombinationCommand(new RecombinationAlgorithm(), new StochasticUniversalSamplingSelector(), 0.3);
	options.recombinationCommands.push_back(constantRecombinationCommand);
	fillDefaultLearningRuleOptions(options);

	return new EvolutionLearningRule(options);
}

AbstractEvolutionWorld* FunctionEvolutionExample::createWorld()
{
	FunctionSimulatorOptions simulatorOptions;
	simulatorOptions.enableGraphics = false;

	return new FunctionSimulator(simulatorOptions, sixHumpCamelFunction);
}

std::string FunctionEvolutionExample::getOriginalName() const
{
	return "Function evolution example";
}

std::string FunctionEvolutionExample::getDescription() const
{
	return "Finds the minimum of the six hump camel back function with the help of evolution!";
}

AbstractTrainingPlan* FunctionEvolutionExample::createNewFromSameType() const
{
	return new FunctionEvolutionExample();
}

std::string FunctionEvolutionExample::getLearningRuleName() const
{
	return EvolutionLearningRule::getName();
}

