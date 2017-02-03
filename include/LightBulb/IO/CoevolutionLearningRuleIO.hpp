#pragma once

#ifndef _COEVOLUTIONLEARNINGRULEIO_H_
#define _COEVOLUTIONLEARNINGRULEIO_H_

// Includes
#include "LightBulb/Learning/Evolution/CoevolutionLearningRule.hpp"
#include "LightBulb/IO/ConstructExisting.hpp"

namespace LightBulb
{
	/**
	* \brief Serializes a CoevolutionLearningRule.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param learningRule The CoevolutionLearningRule to serialize.
	*/
	template <class Archive>
	extern void serialize(Archive& archive, CoevolutionLearningRule& learningRule);
}

namespace cereal
{
	CONSTRUCT_EXISTING(LightBulb::CoevolutionLearningRule, LightBulb::AbstractLearningRule)
	{
		/**
		* \brief Constructs an existing CoevolutionLearningRule.
		* \tparam Archive The archive type.
		* \param ar The archive which should be used.
		* \param learningRule The existing EvolutionLearningRule to construct.
		*/
		template <class Archive>
		static void construct(Archive& ar, LightBulb::CoevolutionLearningRule& learningRule);
	};

}

#endif