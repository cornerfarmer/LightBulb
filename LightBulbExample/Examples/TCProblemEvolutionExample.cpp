#include "TCProblemEvolutionExample.hpp"
#include <Learning/Evolution/RateDifferenceCondition.hpp>
#include <Learning/Evolution/ConstantMutationCommand.hpp>
#include <Learning/Evolution/EvolutionStrategy/MutationAlgorithm.hpp>
#include <Learning/Evolution/BestSelectionCommand.hpp>
#include <Learning/Evolution/ConstantReuseCommand.hpp>
#include <Learning/Evolution/ConstantRecombinationCommand.hpp>
#include <Learning/Evolution/EvolutionStrategy/RecombinationAlgorithm.hpp>
#include <Learning/Evolution/ConstantCreationCommand.hpp>
#include <Learning/Evolution/EvolutionLearningRule.hpp>
#include <Teaching/TeachingLessonBooleanInput.hpp>
#include <Teaching/Teacher.hpp>
#include <NetworkTopology/LayeredNetwork.hpp>
#include <NeuronFactory/DifferentNeuronDescriptionFactory.hpp>
#include <Function/WeightedSumFunction.hpp>
#include <Function/FermiFunction.hpp>
#include <Learning/Evolution/TeachingEvolutionWorld.hpp>
#include <Learning/Evolution/RandomSelector.hpp>
#include <Neuron/NeuronDescription.hpp>
#include <Learning/Evolution/BestReuseSelector.hpp>
#include <Learning/Evolution/ScoreCondition.hpp>
#include <Learning/Evolution/MagnitudeBasedPruningMutationAlgorithm.hpp>
#include <Learning/Evolution/NetworkGrowMutationAlgorithm.hpp>
#include <TrainingPlans/IntegerPreference.hpp>
#include <TrainingPlans/DoublePreference.hpp>
#include "TCProblemTeacher.hpp"

#define PREFERENCE_CREATION_COUNT "Creation count"
#define PREFERENCE_MUTATIONSTRENGTH_CHANGESPEED "Mutationstrength changespeed"
#define PREFERENCE_WEIGHTDECAY_FAC "Weight decay factor"

AbstractLearningRule* TCProblemEvolutionExample::createLearningRate()
{

	EvolutionLearningRuleOptions options;
	options.maxIterationsPerTry = 100000;
	RateDifferenceCondition* rateDifferenceCondition = new RateDifferenceCondition(0.00001, 1000);
	options.exitConditions.push_back(rateDifferenceCondition);
	options.exitConditions.push_back(new ScoreCondition(-0.001));
	ConstantCreationCommand* constantCreationCommand = new ConstantCreationCommand(getIntegerPreference(PREFERENCE_CREATION_COUNT));
	options.creationCommands.push_back(constantCreationCommand);
	options.reuseCommands.push_back(new ConstantReuseCommand(new BestReuseSelector(), 1));
	BestSelectionCommand* bestSelectionCommand = new BestSelectionCommand(80);
	options.selectionCommands.push_back(bestSelectionCommand);

	ConstantMutationCommand* constantMutationCommand = new ConstantMutationCommand(new MutationAlgorithm(getDoublePreference(PREFERENCE_MUTATIONSTRENGTH_CHANGESPEED)), new RandomSelector(new RankBasedRandomFunction()), 2.0);
	options.mutationsCommands.push_back(constantMutationCommand);

	constantMutationCommand = new ConstantMutationCommand(new MagnitudeBasedPruningMutationAlgorithm(1, 0), new RandomSelector(new RankBasedRandomFunction()), 0.03);
	options.mutationsCommands.push_back(constantMutationCommand);

	std::vector<unsigned int> maxNeuronsPerLayer(3);
	maxNeuronsPerLayer[0] = 16;
	maxNeuronsPerLayer[1] = 16;
	maxNeuronsPerLayer[2] = 1;
	constantMutationCommand = new ConstantMutationCommand(new NetworkGrowMutationAlgorithm(maxNeuronsPerLayer), new RandomSelector(new RankBasedRandomFunction()), 0.03);
	//options.mutationsCommands.push_back(constantMutationCommand);

	options.recombinationCommands.push_back(new ConstantRecombinationCommand(new RecombinationAlgorithm(), new RandomSelector(new RankBasedRandomFunction()), 0));
	options.maxTries = 100;
	fillDefaultLearningRuleOptions(&options);

	return new EvolutionLearningRule(options);
}

AbstractEvolutionWorld* TCProblemEvolutionExample::createWorld()
{
	LayeredNetworkOptions* layeredNetworkOptions = new LayeredNetworkOptions();
	layeredNetworkOptions->descriptionFactory = new DifferentNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)), new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)));
	layeredNetworkOptions->neuronsPerLayerCount = std::vector<unsigned int>(3);
	layeredNetworkOptions->neuronsPerLayerCount[0] = 16;
	layeredNetworkOptions->neuronsPerLayerCount[1] = 16;
	layeredNetworkOptions->neuronsPerLayerCount[2] = 1;
	layeredNetworkOptions->useBiasNeuron = true;
	layeredNetworkOptions->enableShortcuts = true;

	TCProblemTeacher* teacher = new TCProblemTeacher(false, getDoublePreference(PREFERENCE_WEIGHTDECAY_FAC));
	
	return new TeachingEvolutionWorld(teacher, *layeredNetworkOptions);
}

TCProblemEvolutionExample::TCProblemEvolutionExample()
{
	addPreference(new IntegerPreference(PREFERENCE_CREATION_COUNT, 200, 80, 300));
	addPreference(new DoublePreference(PREFERENCE_MUTATIONSTRENGTH_CHANGESPEED, 0.0001, 0, 2));
	addPreference(new DoublePreference(PREFERENCE_WEIGHTDECAY_FAC, 0.006, 0.003, 0.3));
}

std::string TCProblemEvolutionExample::getDefaultName()
{
	return "TC-problem evolution example";
}

std::string TCProblemEvolutionExample::getDescription()
{
	return "Teaches a network how to distinguish Ts and Cs with the help of evoultion.";
}

AbstractTrainingPlan* TCProblemEvolutionExample::getCopy()
{
	return new TCProblemEvolutionExample();
}

std::string TCProblemEvolutionExample::getLearningRuleName()
{
	return EvolutionLearningRule::getName();
}

