#include "SimpleReinforcementExample.hpp"
#include <Learning/Evolution/EvolutionLearningRule.hpp>
#include <Learning/Evolution/BipartiteEvolutionLearningRule.hpp>
#include <TrainingPlans/Preferences/IntegerPreference.hpp>
#include <TrainingPlans/Preferences/BooleanPreference.hpp>
#include <NeuronDescription/SameNeuronDescriptionFactory.hpp>
#include <Function/InputFunction/WeightedSumFunction.hpp>
#include <NeuronDescription/NeuronDescription.hpp>
#include <NetworkTopology/FeedForwardNetworkTopology.hpp>
#include <Learning/Reinforcement/PolicyGradientLearningRule.hpp>
#include <Examples/PongEvolution/PongGameFactory.hpp>
#include <Function/ActivationFunction/FermiFunction.hpp>
#include "SimpleReinforcementWorld.hpp"

#define PREFERENCE_EPISODE_SIZE "Episode size"
#define PREFERENCE_SHORTCUT_ENABLE "Enable shortcut connections"
#define PREFERENCE_NEURON_COUNT_FIRST_LAYER "Neuron count in 1. layer"
#define PREFERENCE_SECOND_LAYER_ENABLE "Enable 2. layer"
#define PREFERENCE_NEURON_COUNT_SECOND_LAYER "Neuron count in 2. layer"

using namespace LightBulb;

AbstractLearningRule* SimpleReinforcementExample::createLearningRate()
{
	PolicyGradientLearningRuleOptions options;
	world = createWorld();
	options.world = world;
	options.episodeSize = getIntegerPreference(PREFERENCE_EPISODE_SIZE);
	//options.dataSaveInterval = 100;
	fillDefaultLearningRuleOptions(&options);

	return new PolicyGradientLearningRule(options);
}


SimpleReinforcementWorld* SimpleReinforcementExample::createWorld()
{
	FeedForwardNetworkTopologyOptions options;
	options.enableShortcuts = getBooleanPreference(PREFERENCE_SHORTCUT_ENABLE);

	options.neuronsPerLayerCount.push_back(2);
	options.neuronsPerLayerCount.push_back(getIntegerPreference(PREFERENCE_NEURON_COUNT_FIRST_LAYER));
	if (getBooleanPreference(PREFERENCE_SECOND_LAYER_ENABLE))
		options.neuronsPerLayerCount.push_back(getIntegerPreference(PREFERENCE_NEURON_COUNT_SECOND_LAYER));
	options.neuronsPerLayerCount.push_back(1);

	options.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)));
	

	return new SimpleReinforcementWorld(options);
}


SimpleReinforcementExample::SimpleReinforcementExample()
{
	addCustomSubApp(new PongGameFactory());
	addPreference(new IntegerPreference(PREFERENCE_EPISODE_SIZE, 100, 1, 10000));
	addPreference(new BooleanPreference(PREFERENCE_SHORTCUT_ENABLE, false));
	addPreference(new IntegerPreference(PREFERENCE_NEURON_COUNT_FIRST_LAYER, 3, 1, 30));
	addPreference(new BooleanPreference(PREFERENCE_SECOND_LAYER_ENABLE, false));
	addPreference(new IntegerPreference(PREFERENCE_NEURON_COUNT_SECOND_LAYER, 1, 1, 30));
}

std::string SimpleReinforcementExample::getDefaultName() const
{
	return "Simple reinforcement example";
}

std::string SimpleReinforcementExample::getDescription() const
{
	return "Evolution of a Simple AI with PolicyGradient";
}

AbstractTrainingPlan* SimpleReinforcementExample::getCopy() const
{
	return new SimpleReinforcementExample();
}

std::string SimpleReinforcementExample::getLearningRuleName() const
{
	return PolicyGradientLearningRule::getName();
}


SimpleReinforcementWorld* SimpleReinforcementExample::getWorld()
{
	return world;
}
