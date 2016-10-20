#pragma once

#ifndef _GRADIENTDESCENTLEARNINGRULEPREFERENCEGROUP_H_
#define _GRADIENTDESCENTLEARNINGRULEPREFERENCEGROUP_H_

// Includes
#include "AbstractSupervisedLearningRulePreferenceGroup.hpp"
#include "IO/UseParentSerialization.hpp"
#include "Learning/Supervised/GradientDescentLearningRule.hpp"

namespace LightBulb
{
	// Forward declarations
	class SimpleGradientDescentOptions;
	class ResilientLearningRateOptions;

	class GradientDescentLearningRulePreferenceGroup : public AbstractSupervisedLearningRulePreferenceGroup
	{
	protected:
		void initialize(const GradientDescentLearningRuleOptions& options, const SimpleGradientDescentOptions& simpleGradientDescentOptions, const ResilientLearningRateOptions& resilientLearningRateOptions);
	public:
		GradientDescentLearningRulePreferenceGroup(const std::string& name = "Gradient descent");
		GradientDescentLearningRulePreferenceGroup(const GradientDescentLearningRuleOptions& options, const std::string& name = "Gradient descent");
		GradientDescentLearningRulePreferenceGroup(const GradientDescentLearningRuleOptions& options, const SimpleGradientDescentOptions& simpleGradientDescentOptions, const ResilientLearningRateOptions& resilientLearningRateOptions, const std::string& name = "Gradient descent");

		GradientDescentLearningRuleOptions create() const;
		AbstractPreferenceElement* getCopy() const override;
	};
}

USE_PARENT_SERIALIZATION(LightBulb::GradientDescentLearningRulePreferenceGroup, PreferenceGroup, LightBulb);

#endif
