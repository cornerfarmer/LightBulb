#include "PongPolicyGradientExample.hpp"
#include <Learning/Evolution/EvolutionLearningRule.hpp>
#include <Learning/Evolution/BipartiteEvolutionLearningRule.hpp>
#include <TrainingPlans/IntegerPreference.hpp>
#include <TrainingPlans/BooleanPreference.hpp>
#include <NeuronDescription/SameNeuronDescriptionFactory.hpp>
#include <Function/InputFunction/WeightedSumFunction.hpp>
#include <NeuronDescription/NeuronDescription.hpp>
#include <NetworkTopology/FeedForwardNetworkTopology.hpp>
#include <Learning/Reinforcement/PolicyGradientLearningRule.hpp>
#include <Examples/PongEvolution/PongGameFactory.hpp>
#include "PongReinforcementWorld.hpp"
#include <Function/ActivationFunction/FermiFunction.hpp>
#include "NeuronDescription/DifferentNeuronDescriptionFactory.hpp"
#include "Function/ActivationFunction/RectifierFunction.hpp"
#include "TrainingPlans/DoublePreference.hpp"

#define PREFERENCE_EPISODE_SIZE "Episode size"
#define PREFERENCE_SHORTCUT_ENABLE "Enable shortcut connections"
#define PREFERENCE_BIAS_NEURON "Enable bias neuron"
#define PREFERENCE_NEURON_COUNT_FIRST_LAYER "Neuron count in 1. layer"
#define PREFERENCE_SECOND_LAYER_ENABLE "Enable 2. layer"
#define PREFERENCE_NEURON_COUNT_SECOND_LAYER "Neuron count in 2. layer"
#define PREFERENCE_VALUE_FUNCTION "Value function"
#define PREFERENCE_LEARNING_RATE "learning rate"
#define PREFERENCE_VALUE_LEARNING_RATE "Value learning rate"

using namespace LightBulb;

AbstractLearningRule* PongPolicyGradientExample::createLearningRate()
{
	PolicyGradientLearningRuleOptions options;
	world = createWorld();
	options.world = world;
	options.episodeSize = getIntegerPreference(PREFERENCE_EPISODE_SIZE);
	//options.dataSaveInterval = 100;
	options.seed = 12345;
	fillDefaultLearningRuleOptions(&options);
	options.valueFunctionAsBase = getBooleanPreference(PREFERENCE_VALUE_FUNCTION);
	options.rmsPropLearningRateOptions.learningRate = getDoublePreference(PREFERENCE_LEARNING_RATE);
	options.valueRmsPropLearningRateOptions.learningRate = getDoublePreference(PREFERENCE_VALUE_LEARNING_RATE);

	return new PolicyGradientLearningRule(options);
}


PongReinforcementWorld* PongPolicyGradientExample::createWorld()
{
	FeedForwardNetworkTopologyOptions options;
	options.enableShortcuts = getBooleanPreference(PREFERENCE_SHORTCUT_ENABLE);
	options.useBiasNeuron = getBooleanPreference(PREFERENCE_BIAS_NEURON);

	options.neuronsPerLayerCount.push_back(6);
	options.neuronsPerLayerCount.push_back(getIntegerPreference(PREFERENCE_NEURON_COUNT_FIRST_LAYER));
	if (getBooleanPreference(PREFERENCE_SECOND_LAYER_ENABLE))
		options.neuronsPerLayerCount.push_back(getIntegerPreference(PREFERENCE_NEURON_COUNT_SECOND_LAYER));
	options.neuronsPerLayerCount.push_back(1);

	options.descriptionFactory = new DifferentNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new RectifierFunction()), new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)));
	

	return new PongReinforcementWorld(options);
}


PongPolicyGradientExample::PongPolicyGradientExample()
{
	addCustomSubApp(new PongGameFactory());
	addPreference(new IntegerPreference(PREFERENCE_EPISODE_SIZE, 10, 1, 10000));
	addPreference(new BooleanPreference(PREFERENCE_SHORTCUT_ENABLE, false));
	addPreference(new BooleanPreference(PREFERENCE_BIAS_NEURON, true));
	addPreference(new IntegerPreference(PREFERENCE_NEURON_COUNT_FIRST_LAYER, 25, 1, 30));
	addPreference(new BooleanPreference(PREFERENCE_SECOND_LAYER_ENABLE, false));
	addPreference(new IntegerPreference(PREFERENCE_NEURON_COUNT_SECOND_LAYER, 1, 1, 30));
	addPreference(new BooleanPreference(PREFERENCE_VALUE_FUNCTION, true));
	addPreference(new DoublePreference(PREFERENCE_LEARNING_RATE, 1e-4, 0, 1));
	addPreference(new DoublePreference(PREFERENCE_VALUE_LEARNING_RATE, 1e-4, 0, 1));
}

std::string PongPolicyGradientExample::getDefaultName()
{
	return "Pong policy gradient example";
}

std::string PongPolicyGradientExample::getDescription()
{
	return "Learns pong with policy gradient learning.";
}

AbstractTrainingPlan* PongPolicyGradientExample::getCopy()
{
	return new PongPolicyGradientExample();
}

std::string PongPolicyGradientExample::getLearningRuleName()
{
	return PolicyGradientLearningRule::getName();
}


PongReinforcementWorld* PongPolicyGradientExample::getWorld()
{
	return world;
}
