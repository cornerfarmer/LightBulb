#pragma once

#ifndef _GRADIENTDESCENTLEARNINGRULEPREFERENCEGROUP_H_
#define _GRADIENTDESCENTLEARNINGRULEPREFERENCEGROUP_H_

// Includes
#include "PreferenceGroup.hpp"
#include "IO/UseParentSerialization.hpp"
#include "Learning/Supervised/GradientDescentLearningRule.hpp"

namespace LightBulb
{

	// Forward declarations

	class GradientDescentLearningRulePreferenceGroup : public PreferenceGroup
	{
	protected:
	public:
		GradientDescentLearningRulePreferenceGroup(std::string name = "Gradient descent");

		GradientDescentLearningRuleOptions createOptions();
	};
}

USE_PARENT_SERIALIZATION(LightBulb::GradientDescentLearningRulePreferenceGroup, PreferenceGroup, LightBulb);

#endif
