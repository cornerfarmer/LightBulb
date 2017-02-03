#pragma once

#ifndef _ABSTRACTREINFORCEMENTLEARNINGRULEPREFERENCEGROUP_H_
#define _ABSTRACTREINFORCEMENTLEARNINGRULEPREFERENCEGROUP_H_

// Includes
#include "LightBulb/IO/UseParentSerialization.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/PredefinedPreferenceGroups/AbstractLearningRulePreferenceGroup.hpp"

namespace LightBulb
{
	class AbstractReinforcementLearningRuleOptions;
	/**
	* \brief Describes a predefined preference group for a reinforcement learning rule.
	*/
	class AbstractReinforcementLearningRulePreferenceGroup : public AbstractLearningRulePreferenceGroup
	{
	protected:
		/**
		* \brief Fills the given options with the current value of the contained preferences.
		* \param options The options to fill.
		*/
		void fillOptions(AbstractReinforcementLearningRuleOptions& options) const;
		/**
		* \brief Initializes the preference group.
		* \param options The options which contain the default values.
		*/
		void initialize(const AbstractReinforcementLearningRuleOptions& options);
	public:
		/**
		* \brief Creates a reinforcement learning rule preference group with standard default values.
		* \param name The name.
		*/
		AbstractReinforcementLearningRulePreferenceGroup(const std::string& name = "Reinforcement learning");
		/**
		* \brief Creates a reinforcement learning rule preference group.
		* \param options The options which contain the default values to use.
		* \param name The name.
		*/
		AbstractReinforcementLearningRulePreferenceGroup(const AbstractReinforcementLearningRuleOptions& options, const std::string& name = "Reinforcement learning");
	};
}

USE_PARENT_SERIALIZATION(LightBulb::AbstractReinforcementLearningRulePreferenceGroup, LightBulb::AbstractLearningRulePreferenceGroup, LightBulb);

#endif
