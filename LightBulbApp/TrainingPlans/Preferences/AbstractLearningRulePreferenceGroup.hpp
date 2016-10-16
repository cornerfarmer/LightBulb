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
		void fillOptions(AbstractLearningRuleOptions& options) const;
		void initialize(const AbstractLearningRuleOptions& options);
	public:
		AbstractLearningRulePreferenceGroup(const std::string& name = "Learning");
		AbstractLearningRulePreferenceGroup(const AbstractLearningRuleOptions& options, const std::string& name = "Learning");
	};
}

USE_PARENT_SERIALIZATION(LightBulb::AbstractLearningRulePreferenceGroup, PreferenceGroup, LightBulb);

#endif
