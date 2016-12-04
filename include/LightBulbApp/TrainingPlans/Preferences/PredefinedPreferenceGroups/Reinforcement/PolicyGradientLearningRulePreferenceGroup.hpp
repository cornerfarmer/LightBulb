#pragma once

#ifndef _POLICYGRADIENTLEARNINGRULEPREFERENCEGROUP_H_
#define _POLICYGRADIENTLEARNINGRULEPREFERENCEGROUP_H_

// 
#include "AbstractReinforcementLearningRulePreferenceGroup.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"
#include "LightBulb/Learning/Reinforcement/PolicyGradientLearningRule.hpp"

namespace LightBulb
{
	/**
	* \brief Describes a predefined preference group for a policy gradient learning rule.
	*/
	class PolicyGradientLearningRulePreferenceGroup : public AbstractReinforcementLearningRulePreferenceGroup
	{
	protected:
		/**
		* \brief Initializes the preference group.
		* \param options The options which contain the default values.
		*/
		void initialize(const PolicyGradientLearningRuleOptions& options);
	public:
		/**
		* \brief Creates a policy gradient learning rule preference group with standard default values.
		* \param name The name.
		*/
		PolicyGradientLearningRulePreferenceGroup(const std::string& name = "Poli learning");
		/**
		* \brief Creates a policy gradient learning rule preference group.
		* \param options The options which contain the default values to use.
		* \param name The name.
		*/
		PolicyGradientLearningRulePreferenceGroup(const PolicyGradientLearningRuleOptions& options, const std::string& name = "DQN learning");
		/**
		* \brief Creates gradient descent learning rule options with the current preference values.
		* \return The gradient descent learning rule options.
		*/
		PolicyGradientLearningRuleOptions create() const;
		// Inherited:
		AbstractCloneable* clone() const override;
	};
}

USE_PARENT_SERIALIZATION(LightBulb::PolicyGradientLearningRulePreferenceGroup, LightBulb::AbstractReinforcementLearningRulePreferenceGroup, LightBulb);

#endif
