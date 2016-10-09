#pragma once

#ifndef _ABSTRACTSUPERVISEDLEARNINGRULEPREFERENCEGROUP_H_
#define _ABSTRACTSUPERVISEDLEARNINGRULEPREFERENCEGROUP_H_

// Includes
#include "PreferenceGroup.hpp"
#include "IO/UseParentSerialization.hpp"
#include "Learning/Supervised/GradientDescentLearningRule.hpp"

namespace LightBulb
{

	// Forward declarations

	class AbstractSupervisedLearningRulePreferenceGroup : public PreferenceGroup
	{
	protected:
		void fillOptions(AbstractSupervisedLearningRuleOptions& options);
		void initialize(AbstractSupervisedLearningRuleOptions& options);
	public:
		AbstractSupervisedLearningRulePreferenceGroup(std::string name = "Supervised learning");
		AbstractSupervisedLearningRulePreferenceGroup(AbstractSupervisedLearningRuleOptions& options, std::string name = "Supervised learning");
	};
}

USE_PARENT_SERIALIZATION(LightBulb::AbstractSupervisedLearningRulePreferenceGroup, PreferenceGroup, LightBulb);

#endif
