// Includes
#include "TrainingPlans/Preferences/PredefinedPreferenceGroups/Supervised/GradientDescentLearningRulePreferenceGroup.hpp"
#include "TrainingPlans/Preferences/ChoicePreference.hpp"
#include "TrainingPlans/Preferences/PredefinedPreferenceGroups/Supervised/GradientDescentAlgorithms/SimpleGradientDescentPreferenceGroup.hpp"
#include "TrainingPlans/Preferences/PredefinedPreferenceGroups/Supervised/GradientDescentAlgorithms/ResilientLearningRatePreferenceGroup.hpp"
#include "TrainingPlans/Preferences/PredefinedPreferenceGroups/Supervised/GradientCalculation/BackpropagationPreferenceGroup.hpp"

namespace LightBulb
{
	#define PREFERENCE_GRADIENT_DECENT_ALGORITHM "Gradient decent algorithm"
	#define CHOICE_SIMPLE_GRADIENT_DESCENT "Simple gradient descent"
	#define CHOICE_RESILIENT_LEARNING_RATE "Resilient learning rate"

	GradientDescentLearningRulePreferenceGroup::GradientDescentLearningRulePreferenceGroup(bool skipGradientDescentAlgorithm, const std::string& name)
		:AbstractSupervisedLearningRulePreferenceGroup(name)
	{
		GradientDescentLearningRuleOptions options;
		SimpleGradientDescentOptions simpleGradientDescentOptions;
		ResilientLearningRateOptions resilientLearningRateOptions;
		initialize(skipGradientDescentAlgorithm, options, simpleGradientDescentOptions, resilientLearningRateOptions);
	}

	GradientDescentLearningRulePreferenceGroup::GradientDescentLearningRulePreferenceGroup(const GradientDescentLearningRuleOptions& options, bool skipGradientDescentAlgorithm, const std::string& name)
		:AbstractSupervisedLearningRulePreferenceGroup(options, name)
	{
		SimpleGradientDescentOptions simpleGradientDescentOptions;
		ResilientLearningRateOptions resilientLearningRateOptions;
		initialize(skipGradientDescentAlgorithm, options, simpleGradientDescentOptions, resilientLearningRateOptions);
	}

	GradientDescentLearningRulePreferenceGroup::GradientDescentLearningRulePreferenceGroup(const GradientDescentLearningRuleOptions& options, const SimpleGradientDescentOptions& simpleGradientDescentOptions, const ResilientLearningRateOptions& resilientLearningRateOptions, const std::string& name)
	{
		initialize(false, options, simpleGradientDescentOptions, resilientLearningRateOptions);
	}

	void GradientDescentLearningRulePreferenceGroup::initialize(bool skipGradientDescentAlgorithm, const GradientDescentLearningRuleOptions& options, const SimpleGradientDescentOptions& simpleGradientDescentOptions, const ResilientLearningRateOptions& resilientLearningRateOptions)
	{
		AbstractSupervisedLearningRulePreferenceGroup::initialize(options);
		if (!skipGradientDescentAlgorithm) {
			ChoicePreference* choicePreference = new ChoicePreference(PREFERENCE_GRADIENT_DECENT_ALGORITHM, CHOICE_SIMPLE_GRADIENT_DESCENT);
			choicePreference->addChoice(CHOICE_SIMPLE_GRADIENT_DESCENT);
			choicePreference->addChoice(CHOICE_RESILIENT_LEARNING_RATE);

			addPreference(choicePreference);
			addPreference(new SimpleGradientDescentPreferenceGroup(simpleGradientDescentOptions));
			addPreference(new ResilientLearningRatePreferenceGroup(resilientLearningRateOptions));
		}
		addPreference(new BackpropagationPreferenceGroup());
	}
	
	GradientDescentLearningRuleOptions GradientDescentLearningRulePreferenceGroup::create() const
	{
		GradientDescentLearningRuleOptions options;
		fillOptions(options);

		std::string gradientDescentAlgorithm = "";
		try {
			gradientDescentAlgorithm = getChoicePreference(PREFERENCE_GRADIENT_DECENT_ALGORITHM);
		} catch(std::exception e) {
			gradientDescentAlgorithm = "";
		}

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
