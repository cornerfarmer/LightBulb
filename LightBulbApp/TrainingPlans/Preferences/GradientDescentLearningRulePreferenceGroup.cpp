﻿// Includes
#include "TrainingPlans/Preferences/GradientDescentLearningRulePreferenceGroup.hpp"
#include "SimpleGradientDescentPreferenceGroup.hpp"
#include "BackpropagationPreferenceGroup.hpp"
#include "ResilientLearningRatePreferenceGroup.hpp"

namespace LightBulb
{

	GradientDescentLearningRulePreferenceGroup::GradientDescentLearningRulePreferenceGroup(std::string name)
		:AbstractSupervisedLearningRulePreferenceGroup(name)
	{
		GradientDescentLearningRuleOptions options;
		initialize(options);
	}

	GradientDescentLearningRulePreferenceGroup::GradientDescentLearningRulePreferenceGroup(GradientDescentLearningRuleOptions& options, std::string name)
		:AbstractSupervisedLearningRulePreferenceGroup(options, name)
	{
		initialize(options);
	}

	void GradientDescentLearningRulePreferenceGroup::initialize(GradientDescentLearningRuleOptions& options)
	{
		AbstractSupervisedLearningRulePreferenceGroup::initialize(options);
		addPreference(new SimpleGradientDescentPreferenceGroup());
		addPreference(new ResilientLearningRatePreferenceGroup());
		addPreference(new BackpropagationPreferenceGroup());
	}
	
	GradientDescentLearningRuleOptions GradientDescentLearningRulePreferenceGroup::create()
	{
		GradientDescentLearningRuleOptions options;
		fillOptions(options);
		SimpleGradientDescentOptions gradientDescentOptions = createFromGroup<SimpleGradientDescentOptions, SimpleGradientDescentPreferenceGroup>();
		options.gradientDescentAlgorithm = new SimpleGradientDescent(gradientDescentOptions);
		options.gradientCalculation = createFromGroup<Backpropagation*, BackpropagationPreferenceGroup>();
		return options;
	}

	AbstractPreferenceElement* GradientDescentLearningRulePreferenceGroup::getCopy()
	{
		return new GradientDescentLearningRulePreferenceGroup(*this);
	}

}