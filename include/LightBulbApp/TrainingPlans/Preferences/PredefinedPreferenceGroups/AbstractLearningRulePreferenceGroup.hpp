#pragma once

#ifndef _ABSTRACTLEARNINGRULEPREFERENCEGROUP_H_
#define _ABSTRACTLEARNINGRULEPREFERENCEGROUP_H_

// Includes
#include "TrainingPlans/Preferences/PreferenceGroup.hpp"
#include "Learning/AbstractLearningRule.hpp"
#include "IO/UseParentSerialization.hpp"

namespace LightBulb
{
	/**
	 * \brief Describes a predefined preference group for a learning rule.
	 */
	class AbstractLearningRulePreferenceGroup : public PreferenceGroup
	{
	protected:
		/**
		 * \brief Fills the given options with the current value of the contained preferences.
		 * \param options The options to fill.
		 */
		void fillOptions(AbstractLearningRuleOptions& options) const;
		/**
		 * \brief Initializes the preference group.
		 * \param options The options which contain the default values.
		 */
		void initialize(const AbstractLearningRuleOptions& options);
	public:
		/**
		 * \brief Creates a learning rule preference group with standard default values.
		 * \param name The name.
		 */
		AbstractLearningRulePreferenceGroup(const std::string& name = "Learning");
		/**
		 * \brief Creates a learning rule preference group.
		 * \param options The options which contain the default values to use.
		 * \param name The name.
		 */
		AbstractLearningRulePreferenceGroup(const AbstractLearningRuleOptions& options, const std::string& name = "Learning");
	};
}

USE_PARENT_SERIALIZATION(LightBulb::AbstractLearningRulePreferenceGroup, LightBulb::PreferenceGroup, LightBulb);

#endif
