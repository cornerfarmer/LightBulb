// Includes
#include "TrainingPlans/Preferences/PredefinedPreferenceGroups/Supervised/GradientDescentLearningRulePreferenceGroup.hpp"
#include "TrainingPlans/Preferences/ChoicePreference.hpp"
#include "GradientDescentAlgorithms/SimpleGradientDescentPreferenceGroup.hpp"
#include "GradientDescentAlgorithms/ResilientLearningRatePreferenceGroup.hpp"
#include "GradientCalculation/BackpropagationPreferenceGroup.hpp"

namespace LightBulb
{
	#define PREFERENCE_GRADIENT_DECENT_ALGORITHM "Gradient decent algorithm"
	#define CHOICE_SIMPLE_GRADIENT_DESCENT "Simple gradient descent"
	#define CHOICE_RESILIENT_LEARNING_RATE "Resilient learning rate"

	GradientDescentLearningRulePreferenceGroup::GradientDescentLearningRulePreferenceGroup(const std::string& name)
		:AbstractSupervisedLearningRulePreferenceGroup(name)
	{
		GradientDescentLearningRuleOptions options;
		SimpleGradientDescentOptions simpleGradientDescentOptions;
		ResilientLearningRateOptions resilientLearningRateOptions;
		initialize(options, simpleGradientDescentOptions, resilientLearningRateOptions);
	}

	GradientDescentLearningRulePreferenceGroup::GradientDescentLearningRulePreferenceGroup(const GradientDescentLearningRuleOptions& options, const std::string& name)
		:AbstractSupervisedLearningRulePreferenceGroup(options, name)
	{
		SimpleGradientDescentOptions simpleGradientDescentOptions;
		ResilientLearningRateOptions resilientLearningRateOptions;
		initialize(options, simpleGradientDescentOptions, resilientLearningRateOptions);
	}

	GradientDescentLearningRulePreferenceGroup::GradientDescentLearningRulePreferenceGroup(const GradientDescentLearningRuleOptions& options, const SimpleGradientDescentOptions& simpleGradientDescentOptions, const ResilientLearningRateOptions& resilientLearningRateOptions, const std::string& name)
	{
		initialize(options, simpleGradientDescentOptions, resilientLearningRateOptions);
	}

	void GradientDescentLearningRulePreferenceGroup::initialize(const GradientDescentLearningRuleOptions& options, const SimpleGradientDescentOptions& simpleGradientDescentOptions, const ResilientLearningRateOptions& resilientLearningRateOptions)
	{
		AbstractSupervisedLearningRulePreferenceGroup::initialize(options);
		ChoicePreference* choicePreference = new ChoicePreference(PREFERENCE_GRADIENT_DECENT_ALGORITHM, CHOICE_SIMPLE_GRADIENT_DESCENT);
		choicePreference->addChoice(CHOICE_SIMPLE_GRADIENT_DESCENT);
		choicePreference->addChoice(CHOICE_RESILIENT_LEARNING_RATE);

		addPreference(choicePreference);
		addPreference(new SimpleGradientDescentPreferenceGroup(simpleGradientDescentOptions));
		addPreference(new ResilientLearningRatePreferenceGroup(resilientLearningRateOptions));
		addPreference(new BackpropagationPreferenceGroup());
	}
	
	GradientDescentLearningRuleOptions GradientDescentLearningRulePreferenceGroup::create() const
	{
		GradientDescentLearningRuleOptions options;
		fillOptions(options);
		std::string gradientDescentAlgorithm = getChoicePreference(PREFERENCE_GRADIENT_DECENT_ALGORITHM);

		if (gradientDescentAlgorithm == CHOICE_SIMPLE_GRADIENT_DESCENT)
		{
			SimpleGradientDescentOptions gradientDescentOptions = createFromGroup<SimpleGradientDescentOptions, SimpleGradientDescentPreferenceGroup>();
			options.gradientDescentAlgorithm = new SimpleGradientDescent(gradientDescentOptions);
		} 
		else if (gradientDescentAlgorithm == CHOICE_RESILIENT_LEARNING_RATE)
		{
			ResilientLearningRateOptions resilientLearningRateOptions = createFromGroup<ResilientLearningRateOptions, ResilientLearningRatePreferenceGroup>();
			options.gradientDescentAlgorithm = new ResilientLearningRate(resilientLearningRateOptions);
		}

		options.gradientCalculation = createFromGroup<Backpropagation*, BackpropagationPreferenceGroup>();
		return options;
	}

	AbstractCloneable* GradientDescentLearningRulePreferenceGroup::clone() const
	{
		return new GradientDescentLearningRulePreferenceGroup(*this);
	}

}
