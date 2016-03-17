#include "NetworkEvolutionExample.hpp"
#include <Diagnostic/LearningRuleAnalyser.hpp>
#include <Examples/NetworkSimulator.hpp>
#include <Learning/Evolution/RateDifferenceCondition.hpp>
#include <Learning/Evolution/ConstantMutationCommand.hpp>
#include <Learning/Evolution/EvolutionStrategy/MutationAlgorithm.hpp>
#include <Learning/Evolution/RemainderStochasticSamplingSelector.hpp>
#include <Learning/Evolution/BestSelectionCommand.hpp>
#include <Learning/Evolution/BestReuseCommand.hpp>
#include <Learning/Evolution/ConstantRecombinationCommand.hpp>
#include <Learning/Evolution/EvolutionStrategy/RecombinationAlgorithm.hpp>
#include <Learning/Evolution/ConstantCreationCommand.hpp>
#include <Diagnostic/ChangeableNumber.hpp>
#include <Learning/Evolution/EvolutionLearningRule.hpp>


void doNetworkEvolutionExample()
{
	std::vector<std::vector<float>> consumers(8, std::vector<float>(2));
	consumers[0][0] = 1;
	consumers[0][1] = 1;
	consumers[1][0] = 1;
	consumers[1][1] = -1;

	consumers[2][0] = 2;
	consumers[2][1] = 1;
	consumers[3][0] = 2;
	consumers[3][1] = -1;

	consumers[4][0] = 3;
	consumers[4][1] = 1;
	consumers[5][0] = 3;
	consumers[5][1] = -1;

	consumers[6][0] = 4;
	consumers[6][1] = 1;
	consumers[7][0] = 4;
	consumers[7][1] = -1;

	NetworkSimulator simulator(false, consumers);

	EvolutionLearningRuleOptions options;
	RateDifferenceCondition* rateDifferenceCondition = new RateDifferenceCondition(0.00001, 20);
	options.exitConditions.push_back(rateDifferenceCondition);
	ConstantCreationCommand* constantCreationCommand = new ConstantCreationCommand(20);
	options.creationCommands.push_back(constantCreationCommand);
	options.reuseCommands.push_back(new BestReuseCommand(1));
	BestSelectionCommand* bestSelectionCommand = new BestSelectionCommand(20);
	options.selectionCommands.push_back(bestSelectionCommand);
	MutationAlgorithm* mutationAlgorithm = new MutationAlgorithm(1.6);
	ConstantMutationCommand* constantMutationCommand = new ConstantMutationCommand(mutationAlgorithm, new RemainderStochasticSamplingSelector(), 2.0);
	options.mutationsCommands.push_back(constantMutationCommand);
	options.recombinationCommands.push_back(new ConstantRecombinationCommand(new RecombinationAlgorithm(), new RemainderStochasticSamplingSelector(), 0));
	options.world = &simulator;
	options.enableDebugOutput = false;
	options.scoreGoal = -10.47;
	EvolutionLearningRule learningRule(options);

	LearningRuleAnalyserOptions analyserOptions;
	analyserOptions.learningRule = &learningRule;
	analyserOptions.changableParameters.push_back(new ChangeableNumber<double, MutationAlgorithm>(mutationAlgorithm, &MutationAlgorithm::setMutationStrengthChangeSpeed, 1.3, 0.1, 2.0, "mcs"));
	analyserOptions.changableParameters.push_back(new ChangeableNumber<int, RateDifferenceCondition>(rateDifferenceCondition, &RateDifferenceCondition::setCount, 0, 10, 50, "cnt"));

	LearningRuleAnalyser learningRuleAnalyser(analyserOptions);

	learningRuleAnalyser.execute();

}
