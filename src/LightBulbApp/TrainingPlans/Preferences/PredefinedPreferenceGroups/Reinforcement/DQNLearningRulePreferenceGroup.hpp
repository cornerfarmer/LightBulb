#pragma once

#ifndef _EVOLUTIONLEARNINGRULEPREFERENCEGROUP_H_
#define _EVOLUTIONLEARNINGRULEPREFERENCEGROUP_H_

// 
#include "AbstractReinforcementLearningRulePreferenceGroup.hpp"
#include "IO/UseParentSerialization.hpp"
#include "Learning/Reinforcement/DQNLearningRule.hpp"

namespace LightBulb
{
	/**
	* \brief Describes a predefined preference group for a dqn learning rule.
	*/
	class DQNLearningRulePreferenceGroup : public AbstractReinforcementLearningRulePreferenceGroup
	{
	protected:
		/**
		* \brief Initializes the preference group.
		* \param options The options which contain the default values.
		*/
		void initialize(const DQNLearningRuleOptions& options);
	public:
		/**
		* \brief Creates a dqn learning rule preference group with standard default values.
		* \param name The name.
		*/
		DQNLearningRulePreferenceGroup(const std::string& name = "DQN learning");
		/**
		* \brief Creates a dqn learning rule preference group.
		* \param options The options which contain the default values to use.
		* \param name The name.
		*/
		DQNLearningRulePreferenceGroup(const DQNLearningRuleOptions& options, const std::string& name = "DQN learning");
		/**
		* \brief Creates gradient descent learning rule options with the current preference values.
		* \return The gradient descent learning rule options.
		*/
		DQNLearningRuleOptions create() const;
		// Inherited:
		AbstractCloneable* clone() const override;
	};
}

USE_PARENT_SERIALIZATION(LightBulb::DQNLearningRulePreferenceGroup, LightBulb::AbstractReinforcementLearningRulePreferenceGroup, LightBulb);

#endif
