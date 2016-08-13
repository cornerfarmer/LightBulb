#include "PongDQNExample.hpp"
#include <Learning/Evolution/EvolutionLearningRule.hpp>
#include <Learning/Evolution/BipartiteEvolutionLearningRule.hpp>
#include <TrainingPlans/IntegerPreference.hpp>
#include <TrainingPlans/BooleanPreference.hpp>
#include <NeuronFactory/SameNeuronDescriptionFactory.hpp>
#include <Function/WeightedSumFunction.hpp>
#include <Function/BinaryFunction.hpp>
#include <Neuron/NeuronDescription.hpp>
#include <NetworkTopology/LayeredNetwork.hpp>
#include <Examples/PongEvolution/PongGameFactory.hpp>
#include "PongReinforcementWorld.hpp"
#include <Function/HyperbolicTangentFunction.hpp>
#include <Function/FermiFunction.hpp>
#include <Learning/Reinforcement/DQNLearningRule.hpp>
#include <NeuronFactory/DifferentNeuronDescriptionFactory.hpp>
#include <TrainingPlans/DoublePreference.hpp>

#define PREFERENCE_SHORTCUT_ENABLE "Enable shortcut connections"
#define PREFERENCE_NEURON_COUNT_FIRST_LAYER "Neuron count in 1. layer"
#define PREFERENCE_SECOND_LAYER_ENABLE "Enable 2. layer"
#define PREFERENCE_NEURON_COUNT_SECOND_LAYER "Neuron count in 2. layer"
#define PREFERENCE_LEARNING_RATE "Learning rate"
#define PREFERENCE_MINIBATCH_SIZE "Minibatch size"
#define PREFERENCE_TARGET_NETWORK_UPDATE_FREQUENCY "Target network update frequency"
#define PREFERENCE_REPLAY_MEMORY_SIZE "replay memory size"

AbstractLearningRule* PongDQNExample::createLearningRate()
{
	DQNLearningRuleOptions options;
	world = createWorld();
	options.world = world;
	options.backpropagationOptions.learningRate = getDoublePreference(PREFERENCE_LEARNING_RATE);
	options.minibatchSize = getIntegerPreference(PREFERENCE_MINIBATCH_SIZE);
	options.targetNetworkUpdateFrequency = getIntegerPreference(PREFERENCE_TARGET_NETWORK_UPDATE_FREQUENCY);
	options.replayMemorySize = getIntegerPreference(PREFERENCE_REPLAY_MEMORY_SIZE);

	//options.dataSaveInterval = 100;
	fillDefaultLearningRuleOptions(&options);

	return new DQNLearningRule(options);
}


PongReinforcementWorld* PongDQNExample::createWorld()
{
	LayeredNetworkOptions options;
	options.enableShortcuts = getBooleanPreference(PREFERENCE_SHORTCUT_ENABLE);

	options.neuronsPerLayerCount.push_back(6);
	options.neuronsPerLayerCount.push_back(getIntegerPreference(PREFERENCE_NEURON_COUNT_FIRST_LAYER));
	if (getBooleanPreference(PREFERENCE_SECOND_LAYER_ENABLE))
		options.neuronsPerLayerCount.push_back(getIntegerPreference(PREFERENCE_NEURON_COUNT_SECOND_LAYER));
	options.neuronsPerLayerCount.push_back(2);

	options.descriptionFactory = new DifferentNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)), new NeuronDescription(new WeightedSumFunction(), new IdentityFunction()));
	

	return new PongReinforcementWorld(options, true, 1);
}


PongDQNExample::PongDQNExample()
{
	addCustomSubApp(new PongGameFactory());
	addPreference(new BooleanPreference(PREFERENCE_SHORTCUT_ENABLE, false));
	addPreference(new IntegerPreference(PREFERENCE_NEURON_COUNT_FIRST_LAYER, 10, 1, 30));
	addPreference(new BooleanPreference(PREFERENCE_SECOND_LAYER_ENABLE, false));
	addPreference(new IntegerPreference(PREFERENCE_NEURON_COUNT_SECOND_LAYER, 1, 1, 30));
	addPreference(new DoublePreference(PREFERENCE_LEARNING_RATE, 0.00025, 0, 1));
	addPreference(new IntegerPreference(PREFERENCE_MINIBATCH_SIZE, 32, 1, 1024));
	addPreference(new IntegerPreference(PREFERENCE_TARGET_NETWORK_UPDATE_FREQUENCY, 10000, 1, 100000));
	addPreference(new IntegerPreference(PREFERENCE_REPLAY_MEMORY_SIZE, 1000000, 1, 10000000));
}

std::string PongDQNExample::getDefaultName()
{
	return "Pong DQN example";
}

std::string PongDQNExample::getDescription()
{
	return "Evolution of a Pong AI with DQN.";
}

AbstractTrainingPlan* PongDQNExample::getCopy()
{
	return new PongDQNExample();
}

std::string PongDQNExample::getLearningRuleName()
{
	return PongDQNExample::getName();
}


PongReinforcementWorld* PongDQNExample::getWorld()
{
	return world;
}
