#pragma once

#ifndef _ABSTRACTLEARNINGRULEPREFERENCEGROUP_H_
#define _ABSTRACTLEARNINGRULEPREFERENCEGROUP_H_

// Includes
#include "PreferenceGroup.hpp"
#include "Learning/AbstractLearningRule.hpp"
#include "IO/UseParentSerialization.hpp"

namespace LightBulb
{

	// Forward declarations

	class AbstractLearningRulePreferenceGroup : public PreferenceGroup
	{
	protected:
		void fillOptions(AbstractLearningRuleOptions& options);
		void initialize(AbstractLearningRuleOptions& options);
	public:
		AbstractLearningRulePreferenceGroup(std::string name = "Learning");
		AbstractLearningRulePreferenceGroup(AbstractLearningRuleOptions& options, std::string name = "Learning");
	};
}

USE_PARENT_SERIALIZATION(LightBulb::AbstractLearningRulePreferenceGroup, PreferenceGroup, LightBulb);

#endif
