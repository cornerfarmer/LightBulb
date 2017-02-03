#pragma once

#ifndef _EVOLUTIONLEARNINGRULEPREFERENCEGROUP_H_
#define _EVOLUTIONLEARNINGRULEPREFERENCEGROUP_H_

// Includes
#include "AbstractEvolutionLearningRulePreferenceGroup.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"

namespace LightBulb
{
	class EvolutionLearningRuleOptions;
	/**
	* \brief Describes a predefined preference group for a evolution learning rule.
	*/
	class EvolutionLearningRulePreferenceGroup : public AbstractEvolutionLearningRulePreferenceGroup
	{
	protected:
		/**
		* \brief Initializes the preference group.
		* \param options The options which contain the default values.
		*/
		void initialize(const EvolutionLearningRuleOptions& options);
	public:
		/**
		* \brief Creates a evolution learning rule preference group with standard default values.
		* \param name The name.
		*/
		EvolutionLearningRulePreferenceGroup(const std::string& name = "Evolution learning");
		/**
		* \brief Creates a evolution learning rule preference group.
		* \param options The options which contain the default values to use.
		* \param name The name.
		*/
		EvolutionLearningRulePreferenceGroup(const EvolutionLearningRuleOptions& options, const std::string& name = "Evolution learning");
		/**
		* \brief Creates gradient descent learning rule options with the current preference values.
		* \return The gradient descent learning rule options.
		*/
		EvolutionLearningRuleOptions create() const;
		// Inherited:
		AbstractCloneable* clone() const override;
	};
}

USE_PARENT_SERIALIZATION(LightBulb::EvolutionLearningRulePreferenceGroup, LightBulb::AbstractEvolutionLearningRulePreferenceGroup, LightBulb);

#endif
