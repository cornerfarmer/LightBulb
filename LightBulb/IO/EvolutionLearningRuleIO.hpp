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

template <class Archive>
void serialize(Archive& archive, EvolutionLearningRule& learningRule)
{
	archive(cereal::base_class<AbstractEvolutionLearningRule>(&learningRule));
}

namespace cereal
{
	CONSTRUCT_EXISTING(EvolutionLearningRule, AbstractLearningRule)
	{
		template <class Archive>
		static void construct(Archive& ar, EvolutionLearningRule& learningRule)
		{
			ar(cereal::base_class<AbstractEvolutionLearningRule>(&learningRule));
			learningRule.setHelperToUsedObjects();
		}
	};
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(EvolutionLearningRule);

#endif