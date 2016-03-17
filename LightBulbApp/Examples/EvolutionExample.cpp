#include "EvolutionExample.hpp"
#include <Learning/Evolution/EvolutionLearningRule.hpp>
#include <Examples/Nature.hpp>
#include <Learning/Evolution/ConstantCreationCommand.hpp>
#include <Learning/Evolution/RemainderStochasticSamplingSelector.hpp>
#include <Learning/Evolution/EvolutionStrategy/RecombinationAlgorithm.hpp>
#include <Learning/Evolution/EvolutionStrategy/MutationAlgorithm.hpp>
#include <Learning/Evolution/ConstantRecombinationCommand.hpp>
#include <Learning/Evolution/ConstantMutationCommand.hpp>
#include <Learning/Evolution/BestSelectionCommand.hpp>

void doEvolutionExample()
{
	Nature nature;

	EvolutionLearningRuleOptions options;
	options.creationCommands.push_back(new ConstantCreationCommand(40));
	options.selectionCommands.push_back(new BestSelectionCommand(5));
	options.mutationsCommands.push_back(new ConstantMutationCommand(new MutationAlgorithm(1.6), new RemainderStochasticSamplingSelector(), 23));
	options.recombinationCommands.push_back(new ConstantRecombinationCommand(new RecombinationAlgorithm(), new RemainderStochasticSamplingSelector(), 9));
	options.world = &nature;

	EvolutionLearningRule learningRule(options);

	learningRule.doLearning();

}
