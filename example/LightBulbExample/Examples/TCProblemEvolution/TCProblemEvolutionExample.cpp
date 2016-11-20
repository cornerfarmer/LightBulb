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
#include <NetworkTopology/FeedForwardNetworkTopology.hpp>
#include <NeuronDescription/DifferentNeuronDescriptionFactory.hpp>
#include <Function/InputFunction/WeightedSumFunction.hpp>
#include <Function/ActivationFunction/FermiFunction.hpp>
#include <Learning/Evolution/TeachingEvolutionEnvironment.hpp>
#include <Learning/Evolution/RandomSelector.hpp>
#include <NeuronDescription/NeuronDescription.hpp>
#include <Learning/Evolution/BestReuseSelector.hpp>
#include <Learning/Evolution/FitnessCondition.hpp>
#include <Learning/Evolution/MagnitudeBasedPruningMutationAlgorithm.hpp>
#include <Learning/Evolution/NetworkGrowMutationAlgorithm.hpp>
#include <TrainingPlans/Preferences/IntegerPreference.hpp>
#include <TrainingPlans/Preferences/DoublePreference.hpp>
#include <Learning/Evolution/PhasedTopologyMutationAlgorithm.hpp>
#include "Examples/TCProblemBackpropagation/TCProblemTeacher.hpp"

using namespace LightBulb;

#define PREFERENCE_CREATION_COUNT "Creation count"
#define PREFERENCE_MUTATIONSTRENGTH_CHANGESPEED "Mutationstrength changespeed"
#define PREFERENCE_WEIGHTDECAY_FAC "Weight decay factor"

AbstractLearningRule* TCProblemEvolutionExample::createLearningRate()
{

	EvolutionLearningRuleOptions options;
	options.maxIterationsPerTry = 100000;
	RateDifferenceCondition* rateDifferenceCondition = new RateDifferenceCondition(0.00001, 1000);
	options.exitConditions.push_back(rateDifferenceCondition);
	options.exitConditions.push_back(new FitnessCondition(-0.001));
	ConstantCreationCommand* constantCreationCommand = new ConstantCreationCommand(getIntegerPreference(PREFERENCE_CREATION_COUNT));
	options.creationCommands.push_back(constantCreationCommand);
	options.reuseCommands.push_back(new ConstantReuseCommand(new BestReuseSelector(), 1));
	BestSelectionCommand* bestSelectionCommand = new BestSelectionCommand(80);
	options.selectionCommands.push_back(bestSelectionCommand);

	ConstantMutationCommand* constantMutationCommand = new ConstantMutationCommand(new MutationAlgorithm(getDoublePreference(PREFERENCE_MUTATIONSTRENGTH_CHANGESPEED)), new RandomSelector(new RankBasedRandomFunction()), 2.0);
	options.mutationsCommands.push_back(constantMutationCommand);

	std::vector<unsigned int> maxNeuronsPerLayer(3);
	maxNeuronsPerLayer[0] = 16;
	maxNeuronsPerLayer[1] = 100;
	maxNeuronsPerLayer[2] = 1;
	constantMutationCommand = new ConstantMutationCommand(new PhasedTopologyMutationAlgorithm(new MagnitudeBasedPruningMutationAlgorithm(1, 0), new NetworkGrowMutationAlgorithm(maxNeuronsPerLayer)), new RandomSelector(new RankBasedRandomFunction()), 0.3);
	options.mutationsCommands.push_back(constantMutationCommand);

	options.recombinationCommands.push_back(new ConstantRecombinationCommand(new RecombinationAlgorithm(), new RandomSelector(new RankBasedRandomFunction()), 0));
	options.maxTries = 100;
	fillDefaultLearningRuleOptions(options);

	return new EvolutionLearningRule(options);
}

AbstractEvolutionEnvironment* TCProblemEvolutionExample::createEnvironment()
{
	FeedForwardNetworkTopologyOptions networkTopologyOptions;
	networkTopologyOptions.descriptionFactory = new DifferentNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)), new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)));
	networkTopologyOptions.neuronsPerLayerCount = std::vector<unsigned int>(3);
	networkTopologyOptions.neuronsPerLayerCount[0] = 16;
	networkTopologyOptions.neuronsPerLayerCount[1] = 20;
	networkTopologyOptions.neuronsPerLayerCount[2] = 1;
	networkTopologyOptions.useBiasNeuron = true;
	networkTopologyOptions.enableShortcuts = true;

	TCProblemTeacher* teacher = new TCProblemTeacher(false, getDoublePreference(PREFERENCE_WEIGHTDECAY_FAC));
	
	return new TeachingEvolutionEnvironment(teacher, networkTopologyOptions);
}

TCProblemEvolutionExample::TCProblemEvolutionExample()
{
	addPreference(new IntegerPreference(PREFERENCE_CREATION_COUNT, 200, 80, 300));
	addPreference(new DoublePreference(PREFERENCE_MUTATIONSTRENGTH_CHANGESPEED, 0.0001, 0, 2));
	addPreference(new DoublePreference(PREFERENCE_WEIGHTDECAY_FAC, 0.006, 0.003, 0.3));
}

std::string TCProblemEvolutionExample::getOriginalName() const
{
	return "TC-problem evolution example";
}

std::string TCProblemEvolutionExample::getDescription() const
{
	return "Teaches a network how to distinguish Ts and Cs with the help of evoultion.";
}

AbstractTrainingPlan* TCProblemEvolutionExample::createNewFromSameType() const
{
	return new TCProblemEvolutionExample();
}

std::string TCProblemEvolutionExample::getLearningRuleName() const
{
	return EvolutionLearningRule::getName();
}

