#include "NatureExample.hpp"
#include <Examples/NetworkEvolution/NetworkSimulator.hpp>
#include <Learning/Evolution/RateDifferenceCondition.hpp>
#include <Learning/Evolution/ConstantMutationCommand.hpp>
#include <Learning/Evolution/EvolutionStrategy/MutationAlgorithm.hpp>
#include <Learning/Evolution/RemainderStochasticSamplingSelector.hpp>
#include <Learning/Evolution/BestSelectionCommand.hpp>
#include <Learning/Evolution/ConstantReuseCommand.hpp>
#include <Learning/Evolution/ConstantRecombinationCommand.hpp>
#include <Learning/Evolution/EvolutionStrategy/RecombinationAlgorithm.hpp>
#include <Learning/Evolution/ConstantCreationCommand.hpp>
#include <Learning/Evolution/EvolutionLearningRule.hpp>
#include <Learning/Evolution/BestReuseSelector.hpp>
#include <Learning/Evolution/ScoreCondition.hpp>
#include "Nature.hpp"
#include "NatureFactory.hpp"

using namespace LightBulb;

AbstractLearningRule* NatureExample::createLearningRate()
{
	
	EvolutionLearningRuleOptions options;
	RateDifferenceCondition* rateDifferenceCondition = new RateDifferenceCondition(0.00001, 20);
	options.exitConditions.push_back(rateDifferenceCondition);
	ConstantCreationCommand* constantCreationCommand = new ConstantCreationCommand(20);
	options.creationCommands.push_back(constantCreationCommand);
	options.reuseCommands.push_back(new ConstantReuseCommand(new BestReuseSelector(), 1));
	BestSelectionCommand* bestSelectionCommand = new BestSelectionCommand(20);
	options.selectionCommands.push_back(bestSelectionCommand);
	MutationAlgorithm* mutationAlgorithm = new MutationAlgorithm(1.6);
	ConstantMutationCommand* constantMutationCommand = new ConstantMutationCommand(mutationAlgorithm, new RemainderStochasticSamplingSelector(), 2.0);
	options.mutationsCommands.push_back(constantMutationCommand);
	options.recombinationCommands.push_back(new ConstantRecombinationCommand(new RecombinationAlgorithm(), new RemainderStochasticSamplingSelector(), 0));
	fillDefaultLearningRuleOptions(options);

	return new EvolutionLearningRule(options);
}

AbstractEvolutionWorld* NatureExample::createWorld()
{
	return new Nature();
}

NatureExample::NatureExample()
{
	addCustomSubApp(new NatureFactory());
}

std::string NatureExample::getDefaultName() const
{
	return "Nature evolution example";
}

std::string NatureExample::getDescription() const
{
	return "Does an evolution of based on real nature.";
}

AbstractTrainingPlan* NatureExample::getCopy() const
{
	return new NatureExample();
}

std::string NatureExample::getLearningRuleName() const
{
	return EvolutionLearningRule::getName();
}
