#include "PongMonteCarloExample.hpp"
#include <Learning/Evolution/EvolutionLearningRule.hpp>
#include <Learning/Evolution/BipartiteEvolutionLearningRule.hpp>
#include <TrainingPlans/IntegerPreference.hpp>
#include <TrainingPlans/BooleanPreference.hpp>
#include <Function/InputFunction/WeightedSumFunction.hpp>
#include <Neuron/NeuronDescription.hpp>
#include <NetworkTopology/LayeredNetwork.hpp>
#include <Examples/PongEvolution/PongGameFactory.hpp>
#include "PongReinforcementWorld.hpp"
#include <Function/ActivationFunction/FermiFunction.hpp>
#include <Learning/Reinforcement/MonteCarloLearningRule.hpp>
#include <NeuronFactory/DifferentNeuronDescriptionFactory.hpp>

#define PREFERENCE_SHORTCUT_ENABLE "Enable shortcut connections"
#define PREFERENCE_NEURON_COUNT_FIRST_LAYER "Neuron count in 1. layer"
#define PREFERENCE_SECOND_LAYER_ENABLE "Enable 2. layer"
#define PREFERENCE_NEURON_COUNT_SECOND_LAYER "Neuron count in 2. layer"

AbstractLearningRule* PongMonteCarloExample::createLearningRate()
{
	MonteCarloLearningRuleOptions options;
	world = createWorld();
	options.world = world;
	//options.dataSaveInterval = 100;
	fillDefaultLearningRuleOptions(&options);

	return new MonteCarloLearningRule(options);
}


PongReinforcementWorld* PongMonteCarloExample::createWorld()
{
	LayeredNetworkOptions options;
	options.enableShortcuts = getBooleanPreference(PREFERENCE_SHORTCUT_ENABLE);

	options.neuronsPerLayerCount.push_back(6);
	options.neuronsPerLayerCount.push_back(getIntegerPreference(PREFERENCE_NEURON_COUNT_FIRST_LAYER));
	if (getBooleanPreference(PREFERENCE_SECOND_LAYER_ENABLE))
		options.neuronsPerLayerCount.push_back(getIntegerPreference(PREFERENCE_NEURON_COUNT_SECOND_LAYER));
	options.neuronsPerLayerCount.push_back(2);

	options.descriptionFactory = new DifferentNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)), new NeuronDescription(new WeightedSumFunction(), new IdentityFunction()));
	

	return new PongReinforcementWorld(options, true);
}


PongMonteCarloExample::PongMonteCarloExample()
{
	addCustomSubApp(new PongGameFactory());
	addPreference(new BooleanPreference(PREFERENCE_SHORTCUT_ENABLE, false));
	addPreference(new IntegerPreference(PREFERENCE_NEURON_COUNT_FIRST_LAYER, 10, 1, 30));
	addPreference(new BooleanPreference(PREFERENCE_SECOND_LAYER_ENABLE, false));
	addPreference(new IntegerPreference(PREFERENCE_NEURON_COUNT_SECOND_LAYER, 1, 1, 30));
}

std::string PongMonteCarloExample::getDefaultName()
{
	return "Pong monte carlo example";
}

std::string PongMonteCarloExample::getDescription()
{
	return "Evolution of a Pong AI with monte carlo.";
}

AbstractTrainingPlan* PongMonteCarloExample::getCopy()
{
	return new PongMonteCarloExample();
}

std::string PongMonteCarloExample::getLearningRuleName()
{
	return PongMonteCarloExample::getName();
}


PongReinforcementWorld* PongMonteCarloExample::getWorld()
{
	return world;
}
