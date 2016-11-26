#pragma once

#ifndef _ABSTRACTEVOLUTIONLEARNINGRULEPREFERENCEGROUP_H_
#define _ABSTRACTEVOLUTIONLEARNINGRULEPREFERENCEGROUP_H_

// Includes
#include "AbstractLearningRulePreferenceGroup.hpp"
#include "IO/UseParentSerialization.hpp"
#include "Learning/Evolution/AbstractEvolutionLearningRule.hpp"

namespace LightBulb
{
	/**
	* \brief Describes a predefined preference group for a evolution learning rule.
	*/
	class AbstractEvolutionLearningRulePreferenceGroup : public AbstractLearningRulePreferenceGroup
	{
	protected:
		/**
		* \brief Fills the given options with the current value of the contained preferences.
		* \param options The options to fill.
		*/
		void fillOptions(AbstractEvolutionLearningRuleOptions& options) const;
		/**
		* \brief Initializes the preference group.
		* \param options The options which contain the default values.
		*/
		void initialize(const AbstractEvolutionLearningRuleOptions& options);
	public:
		/**
		* \brief Creates a evolution learning rule preference group with standard default values.
		* \param name The name.
		*/
		AbstractEvolutionLearningRulePreferenceGroup(const std::string& name = "Evolution learning");
		/**
		* \brief Creates a evolution learning rule preference group.
		* \param options The options which contain the default values to use.
		* \param name The name.
		*/
		AbstractEvolutionLearningRulePreferenceGroup(const AbstractEvolutionLearningRuleOptions& options, const std::string& name = "Evolution learning");
	};
}

USE_PARENT_SERIALIZATION(LightBulb::AbstractEvolutionLearningRulePreferenceGroup, LightBulb::AbstractLearningRulePreferenceGroup, LightBulb);

#endif
