#pragma once

#ifndef _ABSTRACTSUPERVISEDLEARNINGRULEPREFERENCEGROUP_H_
#define _ABSTRACTSUPERVISEDLEARNINGRULEPREFERENCEGROUP_H_

// Includes
#include "AbstractLearningRulePreferenceGroup.hpp"
#include "IO/UseParentSerialization.hpp"
#include "Learning/Supervised/AbstractSupervisedLearningRule.hpp"

namespace LightBulb
{
	/**
	* \brief Describes a predefined preference group for a supervised learning rule.
	*/
	class AbstractSupervisedLearningRulePreferenceGroup : public AbstractLearningRulePreferenceGroup
	{
	protected:
		/**
		* \brief Fills the given options with the current value of the contained preferences.
		* \param options The options to fill.
		*/
		void fillOptions(AbstractSupervisedLearningRuleOptions& options) const;
		/**
		* \brief Initializes the preference group.
		* \param options The options which contain the default values.
		*/
		void initialize(const AbstractSupervisedLearningRuleOptions& options);
	public:
		/**
		* \brief Creates a supervised learning rule preference group with standard default values.
		* \param name The name.
		*/
		AbstractSupervisedLearningRulePreferenceGroup(const std::string& name = "Supervised learning");
		/**
		* \brief Creates a supervised learning rule preference group.
		* \param options The options which contain the default values to use.
		* \param name The name.
		*/
		AbstractSupervisedLearningRulePreferenceGroup(const AbstractSupervisedLearningRuleOptions& options, const std::string& name = "Supervised learning");
	};
}

USE_PARENT_SERIALIZATION(LightBulb::AbstractSupervisedLearningRulePreferenceGroup, LightBulb::AbstractLearningRulePreferenceGroup, LightBulb);

#endif
