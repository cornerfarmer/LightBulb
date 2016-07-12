#include "PongReinforcementExample.hpp"
#include <Learning/Evolution/EvolutionLearningRule.hpp>
#include <Learning/Evolution/BipartiteEvolutionLearningRule.hpp>
#include <TrainingPlans/IntegerPreference.hpp>
#include <TrainingPlans/BooleanPreference.hpp>
#include <NeuronFactory/SameNeuronDescriptionFactory.hpp>
#include <Function/WeightedSumFunction.hpp>
#include <Function/BinaryFunction.hpp>
#include <Neuron/NeuronDescription.hpp>
#include <NetworkTopology/LayeredNetwork.hpp>
#include <Learning/Reinforcement/ReinforcementLearningRule.hpp>
#include <Examples/PongEvolution/PongGameFactory.hpp>
#include "PongReinforcementWorld.hpp"
#include <Function/HyperbolicTangentFunction.hpp>
#include <Function/FermiFunction.hpp>

#define PREFERENCE_SHORTCUT_ENABLE "Enable shortcut connections"
#define PREFERENCE_NEURON_COUNT_FIRST_LAYER "Neuron count in 1. layer"
#define PREFERENCE_SECOND_LAYER_ENABLE "Enable 2. layer"
#define PREFERENCE_NEURON_COUNT_SECOND_LAYER "Neuron count in 2. layer"

AbstractLearningRule* PongReinforcementExample::createLearningRate()
{
	ReinforcementLearningRuleOptions options;
	world = createWorld();
	options.world = world;
	//options.dataSaveInterval = 100;
	fillDefaultLearningRuleOptions(&options);

	return new ReinforcementLearningRule(options);
}


PongReinforcementWorld* PongReinforcementExample::createWorld()
{
	LayeredNetworkOptions options;
	options.enableShortcuts = getBooleanPreference(PREFERENCE_SHORTCUT_ENABLE);

	options.neuronsPerLayerCount.push_back(6);
	options.neuronsPerLayerCount.push_back(getIntegerPreference(PREFERENCE_NEURON_COUNT_FIRST_LAYER));
	if (getBooleanPreference(PREFERENCE_SECOND_LAYER_ENABLE))
		options.neuronsPerLayerCount.push_back(getIntegerPreference(PREFERENCE_NEURON_COUNT_SECOND_LAYER));
	options.neuronsPerLayerCount.push_back(1);

	options.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)));
	

	return new PongReinforcementWorld(options);
}


PongReinforcementExample::PongReinforcementExample()
{
	addCustomSubApp(new PongGameFactory());
	addPreference(new BooleanPreference(PREFERENCE_SHORTCUT_ENABLE, false));
	addPreference(new IntegerPreference(PREFERENCE_NEURON_COUNT_FIRST_LAYER, 10, 1, 30));
	addPreference(new BooleanPreference(PREFERENCE_SECOND_LAYER_ENABLE, false));
	addPreference(new IntegerPreference(PREFERENCE_NEURON_COUNT_SECOND_LAYER, 1, 1, 30));
}

std::string PongReinforcementExample::getDefaultName()
{
	return "Pong reinforcement example";
}

std::string PongReinforcementExample::getDescription()
{
	return "Evolution of a Pong AI with reinforcement.";
}

AbstractTrainingPlan* PongReinforcementExample::getCopy()
{
	return new PongReinforcementExample();
}

std::string PongReinforcementExample::getLearningRuleName()
{
	return BipartiteEvolutionLearningRule::getName();
}


PongReinforcementWorld* PongReinforcementExample::getWorld()
{
	return world;
}
