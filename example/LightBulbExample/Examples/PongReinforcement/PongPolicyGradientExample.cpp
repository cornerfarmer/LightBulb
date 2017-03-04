#include "PongPolicyGradientExample.hpp"
#include "Examples/PongEvolution/PongGameFactory.hpp"
#include "PongReinforcementEnvironment.hpp"
#include "LightBulb/Learning/Reinforcement/PolicyGradientLearningRule.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/PredefinedPreferenceGroups/Reinforcement/PolicyGradientLearningRulePreferenceGroup.hpp"
#include "LightBulb/NeuronDescription/DifferentNeuronDescriptionFactory.hpp"
#include "LightBulb/Function/InputFunction/WeightedSumFunction.hpp"
#include "LightBulb/Function/ActivationFunction/RectifierFunction.hpp"
#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/BooleanPreference.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/IntegerPreference.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/NeuronDescription/NeuronDescription.hpp"
#include "LightBulb/Learning/Reinforcement/DefaultReinforcementIndividual.hpp"


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
	PolicyGradientLearningRuleOptions options = createOptions<PolicyGradientLearningRuleOptions, PolicyGradientLearningRulePreferenceGroup>();

	fillDefaultLearningRuleOptions(options);

	return new PolicyGradientLearningRule(options);
}


LightBulb::AbstractReinforcementEnvironment* PongPolicyGradientExample::createEnvironment()
{
	return new PongReinforcementEnvironment();
}

LightBulb::AbstractReinforcementIndividual* PongPolicyGradientExample::createIndividual()
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
	
	return new DefaultReinforcementIndividual(&getEnvironment(), options);
}


PongPolicyGradientExample::PongPolicyGradientExample()
{
	addCustomSubApp(new PongGameFactory());
	addPreference(new BooleanPreference(PREFERENCE_SHORTCUT_ENABLE, false));
	addPreference(new BooleanPreference(PREFERENCE_BIAS_NEURON, true));
	addPreference(new IntegerPreference(PREFERENCE_NEURON_COUNT_FIRST_LAYER, 25, 1, 30));
	addPreference(new BooleanPreference(PREFERENCE_SECOND_LAYER_ENABLE, false));
	addPreference(new IntegerPreference(PREFERENCE_NEURON_COUNT_SECOND_LAYER, 1, 1, 30));

	addPreferenceGroup(new PolicyGradientLearningRulePreferenceGroup());
}

std::string PongPolicyGradientExample::getOriginalName() const
{
	return "Pong policy gradient example";
}

std::string PongPolicyGradientExample::getDescription() const
{
	return "Learns pong with policy gradient learning.";
}

AbstractTrainingPlan* PongPolicyGradientExample::createNewFromSameType() const
{
	return new PongPolicyGradientExample();
}

std::string PongPolicyGradientExample::getLearningRuleName() const
{
	return PolicyGradientLearningRule::getName();
}

