// Includes
#include "LightBulbApp/LightBulbAppPrec.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/PredefinedPreferenceGroups/FeedForwardNetworkTopologyPreferenceGroup.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/DoublePreference.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/BooleanPreference.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/IntegerPreference.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/ChoicePreference.hpp"
#include "LightBulb/Function/ActivationFunction/IdentityFunction.hpp"
#include "LightBulb/NeuronDescription/SameNeuronDescriptionFactory.hpp"
#include "LightBulb/NeuronDescription/DifferentNeuronDescriptionFactory.hpp"
#include "LightBulb/NeuronDescription/NeuronDescription.hpp"
#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
#include "LightBulb/Function/ActivationFunction/RectifierFunction.hpp"
#include "LightBulb/Function/ActivationFunction/HyperbolicTangentFunction.hpp"
#include "LightBulb/Function/ActivationFunction/BinaryFunction.hpp"
#include "LightBulb/Function/InputFunction/WeightedSumFunction.hpp"

namespace LightBulb
{
	#define PREFERENCE_SHORTCUTS "Enable shortcuts"
	#define PREFERENCE_LAYERCOUNT "Layer count"
	#define PREFERENCE_USE_BIAS_NEURON "Use bias neuron"
	#define PREFERENCE_NEURONS_IN_LAYER_X "Neurons in layer "
	#define PREFERENCE_INNER_ACTIVATION_FUNCTION "Inner activation function"
	#define PREFERENCE_OUTPUT_ACTIVATION_FUNCTION "Output activation function"
	#define PREFERENCE_INNER_INPUT_FUNCTION "Inner input function"
	#define PREFERENCE_OUTPUT_INPUT_FUNCTION "Output input function"
	#define CHOICE_ACTIVATION_IDENTITY_FUNCTION "Identity function"
	#define CHOICE_ACTIVATION_FERMI_FUNCTION "Fermi function"
	#define CHOICE_ACTIVATION_BINARY_FUNCTION "Binary function"
	#define CHOICE_ACTIVATION_HYPERBOLIC_TANGENT_FUNCTION "Hyperbolic tangent function"
	#define CHOICE_ACTIVATION_RECTIFIER_FUNCTION "Rectifier function"
	#define CHOICE_INPUT_WEIGHTED_SUM_FUNCTION "Weighted sum function"

	FeedForwardNetworkTopologyPreferenceGroup::FeedForwardNetworkTopologyPreferenceGroup(const std::string& name)
		:PreferenceGroup(name)
	{
		FeedForwardNetworkTopologyOptions options;
		initialize(options);
	}


	FeedForwardNetworkTopologyPreferenceGroup::FeedForwardNetworkTopologyPreferenceGroup(const FeedForwardNetworkTopologyOptions& options, const std::string& name)
		:PreferenceGroup(name)
	{
		initialize(options);
	}

	void FeedForwardNetworkTopologyPreferenceGroup::initialize(const FeedForwardNetworkTopologyOptions& options)
	{
		addPreference(new BooleanPreference(PREFERENCE_SHORTCUTS, options.enableShortcuts));
		addPreference(new BooleanPreference(PREFERENCE_USE_BIAS_NEURON, options.useBiasNeuron));
		addPreference(new IntegerPreference(PREFERENCE_LAYERCOUNT, options.neuronsPerLayerCount.size(), 2, 5));
		for (int i = 0; i < 5; i++)
		{
			addPreference(new IntegerPreference(PREFERENCE_NEURONS_IN_LAYER_X + std::to_string(i + 1), i < options.neuronsPerLayerCount.size() ? options.neuronsPerLayerCount[i] : 10, 1, 50));
		}

		ChoicePreference* innerActivationFunctionPreference = new ChoicePreference(PREFERENCE_INNER_ACTIVATION_FUNCTION, options.descriptionFactory ? getActivationFunctionName(&options.descriptionFactory->getInnerActivationFunction()) : getActivationFunctionName(nullptr));
		fillActivationFunctionChoices(*innerActivationFunctionPreference);
		addPreference(innerActivationFunctionPreference);

		ChoicePreference* outputActivationFunctionPreference = new ChoicePreference(PREFERENCE_OUTPUT_ACTIVATION_FUNCTION, options.descriptionFactory ? getActivationFunctionName(&options.descriptionFactory->getOutputActivationFunction()) : getActivationFunctionName(nullptr));
		fillActivationFunctionChoices(*outputActivationFunctionPreference);
		addPreference(outputActivationFunctionPreference);

		ChoicePreference* innerInputFunctionPreference = new ChoicePreference(PREFERENCE_INNER_INPUT_FUNCTION, options.descriptionFactory ? getInputFunctionName(&options.descriptionFactory->getInnerInputFunction()) : getInputFunctionName(nullptr));
		fillInputFunctionChoices(*innerInputFunctionPreference);
		addPreference(innerInputFunctionPreference);

		ChoicePreference* outputInputFunctionPreference = new ChoicePreference(PREFERENCE_OUTPUT_INPUT_FUNCTION, options.descriptionFactory ? getInputFunctionName(&options.descriptionFactory->getOutputInputFunction()) : getInputFunctionName(nullptr));
		fillInputFunctionChoices(*outputInputFunctionPreference);
		addPreference(outputInputFunctionPreference);
	}

	FeedForwardNetworkTopologyOptions FeedForwardNetworkTopologyPreferenceGroup::create() const
	{
		FeedForwardNetworkTopologyOptions options;
		options.enableShortcuts = getBooleanPreference(PREFERENCE_SHORTCUTS);
		options.useBiasNeuron = getBooleanPreference(PREFERENCE_USE_BIAS_NEURON);
		options.neuronsPerLayerCount.resize(getIntegerPreference(PREFERENCE_LAYERCOUNT));
		for (int i = 0; i < options.neuronsPerLayerCount.size(); i++)
		{
			options.neuronsPerLayerCount[i] = getIntegerPreference(PREFERENCE_NEURONS_IN_LAYER_X + std::to_string(i + 1));
		}

		options.descriptionFactory = new DifferentNeuronDescriptionFactory(new NeuronDescription(getInputFunctionFromChoice(PREFERENCE_INNER_INPUT_FUNCTION), getActivationFunctionFromChoice(PREFERENCE_INNER_ACTIVATION_FUNCTION)), new NeuronDescription(getInputFunctionFromChoice(PREFERENCE_OUTPUT_INPUT_FUNCTION), getActivationFunctionFromChoice(PREFERENCE_OUTPUT_ACTIVATION_FUNCTION)));

		return options;
	}

	AbstractActivationFunction* FeedForwardNetworkTopologyPreferenceGroup::getActivationFunctionFromChoice(std::string preferenceName) const
	{
		std::string activationFunctionName = getChoicePreference(preferenceName);
		if (activationFunctionName == CHOICE_ACTIVATION_IDENTITY_FUNCTION)
			return new IdentityFunction();
		else if (activationFunctionName == CHOICE_ACTIVATION_FERMI_FUNCTION)
			return new FermiFunction();
		else if (activationFunctionName == CHOICE_ACTIVATION_RECTIFIER_FUNCTION)
			return new RectifierFunction();
		else if (activationFunctionName == CHOICE_ACTIVATION_HYPERBOLIC_TANGENT_FUNCTION)
			return new HyperbolicTangentFunction();
		else if (activationFunctionName == CHOICE_ACTIVATION_BINARY_FUNCTION)
			return new BinaryFunction();
		else
			return nullptr;
	}

	AbstractInputFunction* FeedForwardNetworkTopologyPreferenceGroup::getInputFunctionFromChoice(std::string preferenceName) const
	{
		std::string inputFunctionName = getChoicePreference(preferenceName);
		if (inputFunctionName == CHOICE_INPUT_WEIGHTED_SUM_FUNCTION)
			return new WeightedSumFunction();
		else
			return nullptr;
	}

	std::string FeedForwardNetworkTopologyPreferenceGroup::getActivationFunctionName(const AbstractActivationFunction* activationFunction) const
	{
		if (dynamic_cast<const IdentityFunction*>(activationFunction))
			return CHOICE_ACTIVATION_IDENTITY_FUNCTION;
		else if (dynamic_cast<const FermiFunction*>(activationFunction))
			return CHOICE_ACTIVATION_FERMI_FUNCTION;
		else if (dynamic_cast<const RectifierFunction*>(activationFunction))
			return CHOICE_ACTIVATION_RECTIFIER_FUNCTION;
		else if (dynamic_cast<const HyperbolicTangentFunction*>(activationFunction))
			return CHOICE_ACTIVATION_HYPERBOLIC_TANGENT_FUNCTION;
		else if (dynamic_cast<const BinaryFunction*>(activationFunction))
			return CHOICE_ACTIVATION_BINARY_FUNCTION;
		else
			return CHOICE_ACTIVATION_IDENTITY_FUNCTION;
	}

	std::string FeedForwardNetworkTopologyPreferenceGroup::getInputFunctionName(const AbstractInputFunction* inputFunction) const
	{
		if (dynamic_cast<const WeightedSumFunction*>(inputFunction))
			return CHOICE_INPUT_WEIGHTED_SUM_FUNCTION;
		else
			return CHOICE_INPUT_WEIGHTED_SUM_FUNCTION;
	}

	void FeedForwardNetworkTopologyPreferenceGroup::fillInputFunctionChoices(ChoicePreference& preference) const
	{
		preference.addChoice(CHOICE_INPUT_WEIGHTED_SUM_FUNCTION);
	}

	void FeedForwardNetworkTopologyPreferenceGroup::fillActivationFunctionChoices(ChoicePreference& preference) const
	{
		preference.addChoice(CHOICE_ACTIVATION_IDENTITY_FUNCTION);
		preference.addChoice(CHOICE_ACTIVATION_FERMI_FUNCTION);
		preference.addChoice(CHOICE_ACTIVATION_BINARY_FUNCTION);
		preference.addChoice(CHOICE_ACTIVATION_HYPERBOLIC_TANGENT_FUNCTION);
		preference.addChoice(CHOICE_ACTIVATION_RECTIFIER_FUNCTION);
	}

	AbstractCloneable* FeedForwardNetworkTopologyPreferenceGroup::clone() const
	{
		return new FeedForwardNetworkTopologyPreferenceGroup(*this);
	}
}
