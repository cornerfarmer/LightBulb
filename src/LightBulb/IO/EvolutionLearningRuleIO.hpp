#pragma once

#ifndef _EVOLUTIONLEARNINGRULEIO_H_
#define _EVOLUTIONLEARNINGRULEIO_H_

// Includes
#include "Learning/Evolution/EvolutionLearningRule.hpp"
#include "ConstructExisting.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes an EvolutionLearningRule.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param learningRule The EvolutionLearningRule to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, EvolutionLearningRule& learningRule)
	{
		archive(cereal::base_class<AbstractEvolutionLearningRule>(&learningRule));
		archive(cereal::make_nvp("zigguratGenerator", learningRule.zigguratGenerator));
	}
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
		static void construct(Archive& ar, LightBulb::EvolutionLearningRule& learningRule)
		{
			ar(base_class<LightBulb::AbstractEvolutionLearningRule>(&learningRule));
			ar(cereal::make_nvp("zigguratGenerator", learningRule.zigguratGenerator));
			learningRule.setHelperToUsedObjects();
		}
	};
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::EvolutionLearningRule);

#endif