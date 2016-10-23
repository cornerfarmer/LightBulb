#include "PongEvolutionExample.hpp"
#include <Learning/Evolution/ConstantMutationCommand.hpp>
#include <Learning/Evolution/EvolutionStrategy/MutationAlgorithm.hpp>
#include <Learning/Evolution/BestSelectionCommand.hpp>
#include <Learning/Evolution/ConstantReuseCommand.hpp>
#include <Learning/Evolution/ConstantRecombinationCommand.hpp>
#include <Learning/Evolution/EvolutionStrategy/RecombinationAlgorithm.hpp>
#include <Learning/Evolution/ConstantCreationCommand.hpp>
#include <Learning/Evolution/EvolutionLearningRule.hpp>
#include <Learning/Evolution/RandomSelector.hpp>
#include <Learning/Evolution/SharedSamplingCombiningStrategy.hpp>
#include <Learning/Evolution/AbstractHallOfFameAlgorithm.hpp>
#include <Examples/PongEvolution/Pong.hpp>
#include <Learning/Evolution/SharedCoevolutionFitnessFunction.hpp>
#include <Learning/Evolution/PerfectObjectFoundCondition.hpp>
#include <Learning/Evolution/BipartiteEvolutionLearningRule.hpp>
#include <fstream>
#include <Learning/Evolution/BestReuseSelector.hpp>
#include "PongGameFactory.hpp"
#include <TrainingPlans/Preferences/DoublePreference.hpp>
#include <TrainingPlans/Preferences/IntegerPreference.hpp>
#include <TrainingPlans/Preferences/BooleanPreference.hpp>
#include <NeuronDescription/SameNeuronDescriptionFactory.hpp>
#include <Function/InputFunction/WeightedSumFunction.hpp>
#include <Function/ActivationFunction/BinaryFunction.hpp>
#include <NeuronDescription/NeuronDescription.hpp>
#include <NetworkTopology/FeedForwardNetworkTopology.hpp>
#include <Learning/Evolution/MagnitudeBasedPruningMutationAlgorithm.hpp>
#include <Learning/Evolution/WeightDecayFitnessFunction.hpp>
#include <Learning/Evolution/NetworkGrowMutationAlgorithm.hpp>
#include <Learning/Evolution/NeuronDecayFitnessFunction.hpp>
#include <Learning/Evolution/PhasedTopologyMutationAlgorithm.hpp>
#include <Learning/Evolution/RandomHallOfFameAlgorithm.hpp>
#include <Function/ActivationFunction/FermiFunction.hpp>
#include <Function/ActivationFunction/HyperbolicTangentFunction.hpp>

#define PREFERENCE_POPULATION_SIZE "Population size"
#define PREFERENCE_MUTATION_PERCENTAGE "Mutation percentage"
#define PREFERENCE_TOPOLOGY_MUTATION_PERCENTAGE "Topology mutation percentage"
#define PREFERENCE_RECOMBINATION_PERCENTAGE "Recombination percentage"
#define PREFERENCE_COMPETITIONS_SIZE "Competitions per object"
#define PREFERENCE_HALLOFFAME_COMPETITIONS_SIZE "Hall of fame competitions"
#define PREFERENCE_SHORTCUT_ENABLE "Enable shortcut connections"
#define PREFERENCE_NEURON_COUNT_FIRST_LAYER "Neuron count in 1. layer"
#define PREFERENCE_SECOND_LAYER_ENABLE "Enable 2. layer"
#define PREFERENCE_NEURON_COUNT_SECOND_LAYER "Neuron count in 2. layer"
#define PREFERENCE_MUTATIONSTRENGTH_CHANGESPEED "Mutationstrength changespeed"
#define PREFERENCE_WEIGHTDECAY_FAC "Weight decay fac"
#define PREFERENCE_CREATE_UP_TO "Create up to"

using namespace LightBulb;

AbstractLearningRule* PongEvolutionExample::createLearningRate()
{

	EvolutionLearningRuleOptions options;

	options.creationCommands.push_back(new ConstantCreationCommand(getIntegerPreference(PREFERENCE_CREATE_UP_TO)));
	options.exitConditions.push_back(new PerfectObjectFoundCondition(200));
	options.reuseCommands.push_back(new ConstantReuseCommand(new BestReuseSelector(), 16));
	options.selectionCommands.push_back(new BestSelectionCommand(getIntegerPreference(PREFERENCE_POPULATION_SIZE)));
	options.mutationsCommands.push_back(new ConstantMutationCommand(new MutationAlgorithm(getDoublePreference(PREFERENCE_MUTATIONSTRENGTH_CHANGESPEED)), new RandomSelector(new RankBasedRandomFunction()), getDoublePreference(PREFERENCE_MUTATION_PERCENTAGE)));
	options.recombinationCommands.push_back(new ConstantRecombinationCommand(new RecombinationAlgorithm(), new RandomSelector(new RankBasedRandomFunction()), getDoublePreference(PREFERENCE_RECOMBINATION_PERCENTAGE)));
	//options.mutationsCommands.push_back(new ConstantMutationCommand(new MagnitudeBasedPruningMutationAlgorithm(1, 0, true, true), new RandomSelector(new RankBasedRandomFunction()), getDoublePreference(PREFERENCE_TOPOLOGY_MUTATION_PERCENTAGE)));
	//options.fitnessFunctions.push_back(new NeuronDecayFitnessFunction(getDoublePreference(PREFERENCE_WEIGHTDECAY_FAC)));
	std::vector<unsigned int> maxNeuronsPerLayer(4);
	maxNeuronsPerLayer[0] = 6;
	maxNeuronsPerLayer[1] = 100;
	maxNeuronsPerLayer[2] = 100;
	maxNeuronsPerLayer[3] = 2;
	options.mutationsCommands.push_back(new ConstantMutationCommand(new PhasedTopologyMutationAlgorithm(new MagnitudeBasedPruningMutationAlgorithm(1, 0, true, true), new NetworkGrowMutationAlgorithm(maxNeuronsPerLayer), 70), new RandomSelector(new RankBasedRandomFunction()), getDoublePreference(PREFERENCE_TOPOLOGY_MUTATION_PERCENTAGE)));

	//options.fitnessFunctions.push_back(new FitnessSharingFitnessFunction(150));

	fillDefaultEvolutionLearningRule1Options(options);

	//options.recombinationCommands.push_back(new ConstantRecombinationCommand(7));

	EvolutionLearningRule* learningRule1 = new EvolutionLearningRule(options);
	fillDefaultEvolutionLearningRule2Options(options);
	EvolutionLearningRule* learningRule2 = new EvolutionLearningRule(options);

	BipartiteEvolutionLearningRuleOptions bipartiteOptions;
	bipartiteOptions.learningRule1 = learningRule1;
	bipartiteOptions.learningRule2 = learningRule2;
	fillDefaultLearningRuleOptions(bipartiteOptions);

	return new BipartiteEvolutionLearningRule(bipartiteOptions);
}


FeedForwardNetworkTopologyOptions PongEvolutionExample::getNetworkOptions()
{
	FeedForwardNetworkTopologyOptions options;
	options.enableShortcuts = getBooleanPreference(PREFERENCE_SHORTCUT_ENABLE);

	options.neuronsPerLayerCount.push_back(6);
	options.neuronsPerLayerCount.push_back(getIntegerPreference(PREFERENCE_NEURON_COUNT_FIRST_LAYER));
	if (getBooleanPreference(PREFERENCE_SECOND_LAYER_ENABLE))
		options.neuronsPerLayerCount.push_back(getIntegerPreference(PREFERENCE_NEURON_COUNT_SECOND_LAYER));
	options.neuronsPerLayerCount.push_back(2);

	options.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new BinaryFunction()));
	return options;
}

AbstractEvolutionWorld* PongEvolutionExample::createWorld()
{
	cs1 = new SharedSamplingCombiningStrategy(getIntegerPreference(PREFERENCE_COMPETITIONS_SIZE));

	FeedForwardNetworkTopologyOptions options = getNetworkOptions();
	Pong* pong1 = new Pong(options, false, cs1, new SharedCoevolutionFitnessFunction(), hof1, hof2);

	cs1->setSecondWorld(static_cast<Pong&>(*parasiteWorld.get()));
	cs2->setSecondWorld(*pong1);

	return pong1;

}

AbstractEvolutionWorld* PongEvolutionExample::createParasiteWorld()
{
	cs2 = new SharedSamplingCombiningStrategy(getIntegerPreference(PREFERENCE_COMPETITIONS_SIZE));

	hof1 = new RandomHallOfFameAlgorithm(getIntegerPreference(PREFERENCE_HALLOFFAME_COMPETITIONS_SIZE));
	hof2 = new RandomHallOfFameAlgorithm(getIntegerPreference(PREFERENCE_HALLOFFAME_COMPETITIONS_SIZE));

	FeedForwardNetworkTopologyOptions options = getNetworkOptions();
	return new Pong(options, true, cs2, new SharedCoevolutionFitnessFunction(), hof2, hof1);
}

PongEvolutionExample::PongEvolutionExample()
{
	addCustomSubApp(new PongGameFactory());
	addPreference(new DoublePreference(PREFERENCE_MUTATION_PERCENTAGE, 1.8, 0, 3));
	addPreference(new DoublePreference(PREFERENCE_RECOMBINATION_PERCENTAGE, 0.3, 0, 3));
	addPreference(new DoublePreference(PREFERENCE_TOPOLOGY_MUTATION_PERCENTAGE, 0, 0, 3));
	addPreference(new IntegerPreference(PREFERENCE_POPULATION_SIZE, 150, 1, 1000));
	addPreference(new IntegerPreference(PREFERENCE_CREATE_UP_TO, 250, 1, 1000));
	addPreference(new IntegerPreference(PREFERENCE_COMPETITIONS_SIZE, 25, 1, 1000));
	addPreference(new IntegerPreference(PREFERENCE_HALLOFFAME_COMPETITIONS_SIZE, 5, 1, 1000));
	addPreference(new BooleanPreference(PREFERENCE_SHORTCUT_ENABLE, true));
	addPreference(new IntegerPreference(PREFERENCE_NEURON_COUNT_FIRST_LAYER, 10, 1, 30));
	addPreference(new BooleanPreference(PREFERENCE_SECOND_LAYER_ENABLE, false));
	addPreference(new IntegerPreference(PREFERENCE_NEURON_COUNT_SECOND_LAYER, 1, 1, 30));
	addPreference(new DoublePreference(PREFERENCE_MUTATIONSTRENGTH_CHANGESPEED, 1.6, 0, 2)); // 1.6, simple
	addPreference(new DoublePreference(PREFERENCE_WEIGHTDECAY_FAC, 0, 0.003, 0.3));
}

std::string PongEvolutionExample::getDefaultName() const
{
	return "Pong evolution example";
}

std::string PongEvolutionExample::getDescription() const
{
	return "Evolution of a Pong AI with coevolution.";
}

AbstractTrainingPlan* PongEvolutionExample::getCopy() const
{
	return new PongEvolutionExample();
}

std::string PongEvolutionExample::getLearningRuleName() const
{
	return BipartiteEvolutionLearningRule::getName();
}

