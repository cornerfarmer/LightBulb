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

	class GradientDescentLearningRulePreferenceGroup : public AbstractSupervisedLearningRulePreferenceGroup
	{
	protected:
		void initialize(GradientDescentLearningRuleOptions& options);
	public:
		GradientDescentLearningRulePreferenceGroup(std::string name = "Gradient descent");
		GradientDescentLearningRulePreferenceGroup(GradientDescentLearningRuleOptions& options, std::string name = "Gradient descent");

		GradientDescentLearningRuleOptions create();
		AbstractPreferenceElement* getCopy() override;
	};
}

USE_PARENT_SERIALIZATION(LightBulb::GradientDescentLearningRulePreferenceGroup, PreferenceGroup, LightBulb);

#endif
