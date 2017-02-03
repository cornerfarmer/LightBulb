#pragma once

#ifndef _EVOLUTIONLEARNINGRULEIO_H_
#define _EVOLUTIONLEARNINGRULEIO_H_

// Includes
#include "LightBulb/Learning/Evolution/EvolutionLearningRule.hpp"
#include "LightBulb/IO/ConstructExisting.hpp"

namespace LightBulb
{
	/**
	* \brief Serializes an EvolutionLearningRule.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param learningRule The EvolutionLearningRule to serialize.
	*/
	template <class Archive>
	extern void serialize(Archive& archive, EvolutionLearningRule& learningRule);
}

namespace cereal
{
	CONSTRUCT_EXISTING(LightBulb::EvolutionLearningRule, LightBulb::AbstractLearningRule)
	{
		/**
		* \brief Constructs an existing EvolutionLearningRule.
		* \tparam Archive The archive type.
		* \param ar The archive which should be used.
		* \param learningRule The existing EvolutionLearningRule to construct.
		*/
		template <class Archive>
		static void construct(Archive& ar, LightBulb::EvolutionLearningRule& learningRule);
	};
}

#include "LightBulb/IO/TemplateDeclaration.hpp"
CEREAL_FORCE_DYNAMIC_INIT_FIXED(EvolutionLearningRule)

#endif