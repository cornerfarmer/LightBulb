#include "SimpleReinforcementDQNExample.hpp"
#include <Learning/Evolution/EvolutionLearningRule.hpp>
#include <Learning/Evolution/BipartiteEvolutionLearningRule.hpp>
#include <TrainingPlans/Preferences/IntegerPreference.hpp>
#include <TrainingPlans/Preferences/BooleanPreference.hpp>
#include <Function/InputFunction/WeightedSumFunction.hpp>
#include <NeuronDescription/NeuronDescription.hpp>
#include <NetworkTopology/FeedForwardNetworkTopology.hpp>
#include "SimpleReinforcementWorld.hpp"
#include <Function/ActivationFunction/FermiFunction.hpp>
#include <Learning/Reinforcement/DQNLearningRule.hpp>
#include <NeuronDescription/DifferentNeuronDescriptionFactory.hpp>
#include <TrainingPlans/Preferences/DoublePreference.hpp>

#define PREFERENCE_SHORTCUT_ENABLE "Enable shortcut connections"
#define PREFERENCE_NEURON_COUNT_FIRST_LAYER "Neuron count in 1. layer"
#define PREFERENCE_SECOND_LAYER_ENABLE "Enable 2. layer"
#define PREFERENCE_NEURON_COUNT_SECOND_LAYER "Neuron count in 2. layer"
#define PREFERENCE_LEARNING_RATE "Learning rate"
#define PREFERENCE_MINIBATCH_SIZE "Minibatch size"
#define PREFERENCE_TARGET_NETWORK_UPDATE_FREQUENCY "Target network update frequency"
#define PREFERENCE_REPLAY_MEMORY_SIZE "replay memory size"
#define PREFERENCE_FINAL_EXPLORATION_FRAME "final exploration frame"
#define PREFERENCE_RMSMPROP_LEARNING_RATE "RMSProp learning rate"

using namespace LightBulb;

AbstractLearningRule* SimpleReinforcementDQNExample::createLearningRate()
{
	DQNLearningRuleOptions options;
	world = createWorld();
	options.world = world;
	options.rmsPropOptions.learningRate = getDoublePreference(PREFERENCE_LEARNING_RATE);
	options.minibatchSize = getIntegerPreference(PREFERENCE_MINIBATCH_SIZE);
	options.targetNetworkUpdateFrequency = getIntegerPreference(PREFERENCE_TARGET_NETWORK_UPDATE_FREQUENCY);
	options.replayMemorySize = getIntegerPreference(PREFERENCE_REPLAY_MEMORY_SIZE);
	options.finalExplorationFrame = getIntegerPreference(PREFERENCE_FINAL_EXPLORATION_FRAME);
	//options.dataSaveInterval = 100;
	fillDefaultLearningRuleOptions(&options);

	return new DQNLearningRule(options);
}


SimpleReinforcementWorld* SimpleReinforcementDQNExample::createWorld()
{
	FeedForwardNetworkTopologyOptions options;
	options.enableShortcuts = getBooleanPreference(PREFERENCE_SHORTCUT_ENABLE);

	options.neuronsPerLayerCount.push_back(4);
	options.neuronsPerLayerCount.push_back(getIntegerPreference(PREFERENCE_NEURON_COUNT_FIRST_LAYER));
	if (getBooleanPreference(PREFERENCE_SECOND_LAYER_ENABLE))
		options.neuronsPerLayerCount.push_back(getIntegerPreference(PREFERENCE_NEURON_COUNT_SECOND_LAYER));
	options.neuronsPerLayerCount.push_back(4);

	options.descriptionFactory = new DifferentNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)), new NeuronDescription(new WeightedSumFunction(), new IdentityFunction()));
	

	return new SimpleReinforcementWorld(options, true, 1);
}


SimpleReinforcementDQNExample::SimpleReinforcementDQNExample()
{
	addPreference(new BooleanPreference(PREFERENCE_SHORTCUT_ENABLE, false));
	addPreference(new IntegerPreference(PREFERENCE_NEURON_COUNT_FIRST_LAYER, 10, 1, 30));
	addPreference(new BooleanPreference(PREFERENCE_SECOND_LAYER_ENABLE, false));
	addPreference(new IntegerPreference(PREFERENCE_NEURON_COUNT_SECOND_LAYER, 1, 1, 30));
	addPreference(new DoublePreference(PREFERENCE_LEARNING_RATE, 0.00025, 0, 1));
	addPreference(new IntegerPreference(PREFERENCE_MINIBATCH_SIZE, 32, 1, 1024));
	addPreference(new IntegerPreference(PREFERENCE_TARGET_NETWORK_UPDATE_FREQUENCY, 10000, 1, 100000));
	addPreference(new IntegerPreference(PREFERENCE_REPLAY_MEMORY_SIZE, 1000000, 1, 10000000));
	addPreference(new IntegerPreference(PREFERENCE_FINAL_EXPLORATION_FRAME, 1000000, 1, 1000000));
	addPreference(new BooleanPreference(PREFERENCE_RMSMPROP_LEARNING_RATE, false));
}

std::string SimpleReinforcementDQNExample::getDefaultName() const
{
	return "Simple DQN example";
}

std::string SimpleReinforcementDQNExample::getDescription() const
{
	return "Evolution of a Simple AI with DQN.";
}

AbstractTrainingPlan* SimpleReinforcementDQNExample::getCopy() const
{
	return new SimpleReinforcementDQNExample();
}

std::string SimpleReinforcementDQNExample::getLearningRuleName() const
{
	return SimpleReinforcementDQNExample::getName();
}


SimpleReinforcementWorld* SimpleReinforcementDQNExample::getWorld()
{
	return world;
}
