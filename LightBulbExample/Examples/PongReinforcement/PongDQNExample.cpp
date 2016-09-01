#include "PongDQNExample.hpp"
#include <Learning/Evolution/EvolutionLearningRule.hpp>
#include <Learning/Evolution/BipartiteEvolutionLearningRule.hpp>
#include <TrainingPlans/IntegerPreference.hpp>
#include <TrainingPlans/BooleanPreference.hpp>
#include <Function/InputFunction//WeightedSumFunction.hpp>
#include <Neuron/NeuronDescription.hpp>
#include <NetworkTopology/FeedForwardNetworkTopology.hpp>
#include <Examples/PongEvolution/PongGameFactory.hpp>
#include "PongReinforcementWorld.hpp"
#include <Learning/Reinforcement/DQNLearningRule.hpp>
#include <NeuronFactory/DifferentNeuronDescriptionFactory.hpp>
#include <TrainingPlans/DoublePreference.hpp>
#include <Function/ActivationFunction/RectifierFunction.hpp>

#define PREFERENCE_SHORTCUT_ENABLE "Enable shortcut connections"
#define PREFERENCE_NEURON_COUNT_FIRST_LAYER "Neuron count in 1. layer"
#define PREFERENCE_SECOND_LAYER_ENABLE "Enable 2. layer"
#define PREFERENCE_NEURON_COUNT_SECOND_LAYER "Neuron count in 2. layer"
#define PREFERENCE_USE_BIAS_NEURON "Use bias neuron"
#define PREFERENCE_LEARNING_RATE "Learning rate"
#define PREFERENCE_MINIBATCH_SIZE "Minibatch size"
#define PREFERENCE_TARGET_NETWORK_UPDATE_FREQUENCY "Target network update frequency"
#define PREFERENCE_REPLAY_MEMORY_SIZE "replay memory size"
#define PREFERENCE_FINAL_EXPLORATION_FRAME "final exploration frame"
#define PREFERENCE_CLIP_ERROR "Clip error"
#define PREFERENCE_RMSMPROP_LEARNING_RATE "RMSProp learning rate"
#define PREFERENCE_MOMENTUM "Momentum"
#define PREFERENCE_REPLAY_START_SIZE "Replay start size"
#define PREFERENCE_DISCOUNT_FACTOR "Discount factor"
#define PREFERENCE_REPLACE_STORED_TRANSITIONS "Replace stored transitions"

AbstractLearningRule* PongDQNExample::createLearningRate()
{
	DQNLearningRuleOptions options;
	world = createWorld();
	options.world = world;
	options.minibatchSize = getIntegerPreference(PREFERENCE_MINIBATCH_SIZE);
	options.targetNetworkUpdateFrequency = getIntegerPreference(PREFERENCE_TARGET_NETWORK_UPDATE_FREQUENCY);
	options.replayMemorySize = getIntegerPreference(PREFERENCE_REPLAY_MEMORY_SIZE);
	options.finalExplorationFrame = getIntegerPreference(PREFERENCE_FINAL_EXPLORATION_FRAME);
	options.replayStartSize = getIntegerPreference(PREFERENCE_REPLAY_START_SIZE);
	options.gradientDecentOptions.clipError = getBooleanPreference(PREFERENCE_CLIP_ERROR);
	options.rmsPropOptions.learningRate = getDoublePreference(PREFERENCE_LEARNING_RATE);
	options.rmsPropOptions.deltaWeightsMomentum = getDoublePreference(PREFERENCE_MOMENTUM);
	options.discountFactor = getDoublePreference(PREFERENCE_DISCOUNT_FACTOR);
	options.replaceStoredTransitions = getBooleanPreference(PREFERENCE_REPLACE_STORED_TRANSITIONS);


	//options.dataSaveInterval = 100;
	fillDefaultLearningRuleOptions(&options);

	return new DQNLearningRule(options);
}


PongReinforcementWorld* PongDQNExample::createWorld()
{
	FeedForwardNetworkTopologyOptions options;
	options.enableShortcuts = getBooleanPreference(PREFERENCE_SHORTCUT_ENABLE);
	options.useBiasNeuron = getBooleanPreference(PREFERENCE_USE_BIAS_NEURON);

	options.neuronsPerLayerCount.push_back(6);
	options.neuronsPerLayerCount.push_back(getIntegerPreference(PREFERENCE_NEURON_COUNT_FIRST_LAYER));
	if (getBooleanPreference(PREFERENCE_SECOND_LAYER_ENABLE))
		options.neuronsPerLayerCount.push_back(getIntegerPreference(PREFERENCE_NEURON_COUNT_SECOND_LAYER));
	options.neuronsPerLayerCount.push_back(3);

	options.descriptionFactory = new DifferentNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new RectifierFunction()), new NeuronDescription(new WeightedSumFunction(), new IdentityFunction()));
	

	return new PongReinforcementWorld(options, true, 1);
}


PongDQNExample::PongDQNExample()
{
	addCustomSubApp(new PongGameFactory());
	addPreference(new BooleanPreference(PREFERENCE_SHORTCUT_ENABLE, false));
	addPreference(new BooleanPreference(PREFERENCE_USE_BIAS_NEURON, true));
	addPreference(new IntegerPreference(PREFERENCE_NEURON_COUNT_FIRST_LAYER, 512, 1, 30));
	addPreference(new BooleanPreference(PREFERENCE_SECOND_LAYER_ENABLE, false));
	addPreference(new IntegerPreference(PREFERENCE_NEURON_COUNT_SECOND_LAYER, 1, 1, 30));
	addPreference(new DoublePreference(PREFERENCE_LEARNING_RATE, 0.00025, 0, 1));
	addPreference(new IntegerPreference(PREFERENCE_MINIBATCH_SIZE, 32, 1, 1024));
	addPreference(new IntegerPreference(PREFERENCE_TARGET_NETWORK_UPDATE_FREQUENCY, 10000, 1, 100000));
	addPreference(new IntegerPreference(PREFERENCE_REPLAY_MEMORY_SIZE, 1000000, 1, 10000000));
	addPreference(new IntegerPreference(PREFERENCE_FINAL_EXPLORATION_FRAME, 1000000, 1, 1000000));
	addPreference(new BooleanPreference(PREFERENCE_CLIP_ERROR, true));
	addPreference(new BooleanPreference(PREFERENCE_RMSMPROP_LEARNING_RATE, true));
	addPreference(new DoublePreference(PREFERENCE_MOMENTUM, 0, 0, 1));
	addPreference(new IntegerPreference(PREFERENCE_REPLAY_START_SIZE, 50000, 1, 50000));
	addPreference(new DoublePreference(PREFERENCE_DISCOUNT_FACTOR, 0.99, 0, 1));
	addPreference(new BooleanPreference(PREFERENCE_REPLACE_STORED_TRANSITIONS, true));
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
