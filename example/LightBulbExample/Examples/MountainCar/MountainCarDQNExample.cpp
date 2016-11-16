#include "MountainCarDQNExample.hpp"
#include <Learning/Evolution/EvolutionLearningRule.hpp>
#include <Learning/Evolution/BipartiteEvolutionLearningRule.hpp>
#include <TrainingPlans/Preferences/IntegerPreference.hpp>
#include <TrainingPlans/Preferences/BooleanPreference.hpp>
#include <Function/InputFunction/WeightedSumFunction.hpp>
#include <NeuronDescription/NeuronDescription.hpp>
#include <NetworkTopology/FeedForwardNetworkTopology.hpp>
#include "MountainCarWorld.hpp"
#include <Learning/Reinforcement/DQNLearningRule.hpp>
#include <NeuronDescription/DifferentNeuronDescriptionFactory.hpp>
#include <TrainingPlans/Preferences/DoublePreference.hpp>
#include "MountainCarFactory.hpp"
#include <Function/ActivationFunction/RectifierFunction.hpp>

#define PREFERENCE_SHORTCUT_ENABLE "Enable shortcut connections"
#define PREFERENCE_NEURON_COUNT_FIRST_LAYER "Neuron count in 1. layer"
#define PREFERENCE_SECOND_LAYER_ENABLE "Enable 2. layer"
#define PREFERENCE_NEURON_COUNT_SECOND_LAYER "Neuron count in 2. layer"
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

using namespace LightBulb;

AbstractLearningRule* MountainCarDQNExample::createLearningRate()
{
	DQNLearningRuleOptions options;
	world = createWorld();
	options.world = world;
	options.minibatchSize = getIntegerPreference(PREFERENCE_MINIBATCH_SIZE);
	options.targetNetworkUpdateFrequency = getIntegerPreference(PREFERENCE_TARGET_NETWORK_UPDATE_FREQUENCY);
	options.replayMemorySize = getIntegerPreference(PREFERENCE_REPLAY_MEMORY_SIZE);
	options.finalExplorationFrame = getIntegerPreference(PREFERENCE_FINAL_EXPLORATION_FRAME);
	options.replayStartSize = getIntegerPreference(PREFERENCE_REPLAY_START_SIZE);
	options.gradientDescentOptions.clipError = getBooleanPreference(PREFERENCE_CLIP_ERROR);
	options.rmsPropOptions.learningRate = getDoublePreference(PREFERENCE_LEARNING_RATE);
	options.rmsPropOptions.deltaWeightsMomentum = getDoublePreference(PREFERENCE_MOMENTUM);
	options.discountFactor = getDoublePreference(PREFERENCE_DISCOUNT_FACTOR);
	options.replaceStoredTransitions = getBooleanPreference(PREFERENCE_REPLACE_STORED_TRANSITIONS);
	//options.dataSaveInterval = 100;
	fillDefaultLearningRuleOptions(options);

	return new DQNLearningRule(options);
}


MountainCarWorld* MountainCarDQNExample::createWorld()
{
	FeedForwardNetworkTopologyOptions options;
	options.enableShortcuts = getBooleanPreference(PREFERENCE_SHORTCUT_ENABLE);

	options.neuronsPerLayerCount.push_back(2);
	options.neuronsPerLayerCount.push_back(getIntegerPreference(PREFERENCE_NEURON_COUNT_FIRST_LAYER));
	if (getBooleanPreference(PREFERENCE_SECOND_LAYER_ENABLE))
		options.neuronsPerLayerCount.push_back(getIntegerPreference(PREFERENCE_NEURON_COUNT_SECOND_LAYER));
	options.neuronsPerLayerCount.push_back(3);

	options.descriptionFactory = new DifferentNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new RectifierFunction(0.2)), new NeuronDescription(new WeightedSumFunction(), new IdentityFunction()));
	

	return new MountainCarWorld(options, true, 1);
}


MountainCarDQNExample::MountainCarDQNExample()
{
	addCustomSubApp(new MountainCarFactory());
	addPreference(new BooleanPreference(PREFERENCE_SHORTCUT_ENABLE, false));
	addPreference(new IntegerPreference(PREFERENCE_NEURON_COUNT_FIRST_LAYER, 60, 1, 30));
	addPreference(new BooleanPreference(PREFERENCE_SECOND_LAYER_ENABLE, false));
	addPreference(new IntegerPreference(PREFERENCE_NEURON_COUNT_SECOND_LAYER, 1, 1, 30));
	addPreference(new DoublePreference(PREFERENCE_LEARNING_RATE, 0.0025, 0, 1));
	addPreference(new IntegerPreference(PREFERENCE_MINIBATCH_SIZE, 32, 1, 1024));
	addPreference(new IntegerPreference(PREFERENCE_TARGET_NETWORK_UPDATE_FREQUENCY, 1000, 1, 100000));
	addPreference(new IntegerPreference(PREFERENCE_REPLAY_MEMORY_SIZE, 10000, 1, 10000000));
	addPreference(new IntegerPreference(PREFERENCE_FINAL_EXPLORATION_FRAME, 10000, 1, 1000000));
	addPreference(new BooleanPreference(PREFERENCE_CLIP_ERROR, false));
	addPreference(new BooleanPreference(PREFERENCE_RMSMPROP_LEARNING_RATE, true));
	addPreference(new DoublePreference(PREFERENCE_MOMENTUM, 0, 0, 1));
	addPreference(new IntegerPreference(PREFERENCE_REPLAY_START_SIZE, 2000, 1, 50000));
	addPreference(new DoublePreference(PREFERENCE_DISCOUNT_FACTOR, 0.99, 0, 1));
	addPreference(new BooleanPreference(PREFERENCE_REPLACE_STORED_TRANSITIONS, true));
}

std::string MountainCarDQNExample::getOriginalName() const
{
	return "MountainCar DQN example";
}

std::string MountainCarDQNExample::getDescription() const
{
	return "Evolution of a MountainCar AI with DQN.";
}

AbstractTrainingPlan* MountainCarDQNExample::createNewFromSameType() const
{
	return new MountainCarDQNExample();
}

std::string MountainCarDQNExample::getLearningRuleName() const
{
	return getName();
}


MountainCarWorld& MountainCarDQNExample::getWorld()
{
	return *world;
}
