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
		void fillOptions(AbstractSupervisedLearningRuleOptions& options);
		void initialize(AbstractSupervisedLearningRuleOptions& options);
	public:
		AbstractSupervisedLearningRulePreferenceGroup(std::string name = "Supervised learning");
		AbstractSupervisedLearningRulePreferenceGroup(AbstractSupervisedLearningRuleOptions& options, std::string name = "Supervised learning");
	};
}

USE_PARENT_SERIALIZATION(LightBulb::AbstractSupervisedLearningRulePreferenceGroup, AbstractLearningRulePreferenceGroup, LightBulb);

#endif
