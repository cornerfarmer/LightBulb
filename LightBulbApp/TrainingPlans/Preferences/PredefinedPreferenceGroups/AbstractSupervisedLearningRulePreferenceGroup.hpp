#pragma once

#ifndef _ABSTRACTSUPERVISEDLEARNINGRULEPREFERENCEGROUP_H_
#define _ABSTRACTSUPERVISEDLEARNINGRULEPREFERENCEGROUP_H_

// Includes
#include "AbstractLearningRulePreferenceGroup.hpp"
#include "IO/UseParentSerialization.hpp"
#include "Learning/Supervised/AbstractSupervisedLearningRule.hpp"

namespace LightBulb
{

	// Forward declarations

	class AbstractSupervisedLearningRulePreferenceGroup : public AbstractLearningRulePreferenceGroup
	{
	protected:
		void fillOptions(AbstractSupervisedLearningRuleOptions& options) const;
		void initialize(const AbstractSupervisedLearningRuleOptions& options);
	public:
		AbstractSupervisedLearningRulePreferenceGroup(const std::string& name = "Supervised learning");
		AbstractSupervisedLearningRulePreferenceGroup(const AbstractSupervisedLearningRuleOptions& options, const std::string& name = "Supervised learning");
	};
}

USE_PARENT_SERIALIZATION(LightBulb::AbstractSupervisedLearningRulePreferenceGroup, AbstractLearningRulePreferenceGroup, LightBulb);

#endif
