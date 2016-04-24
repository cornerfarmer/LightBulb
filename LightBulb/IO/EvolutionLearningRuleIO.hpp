#pragma once

#ifndef _EVOLUTIONLEARNINGRULEIO_H_
#define _EVOLUTIONLEARNINGRULEIO_H_

// Includes
#include "Learning/Evolution/EvolutionLearningRule.hpp"
#include "IOStorage.hpp"

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
	template <> struct LoadAndConstruct<EvolutionLearningRule>
	{
		template <class Archive>
		static void load_and_construct(Archive& ar, cereal::construct<EvolutionLearningRule>& construct)
		{
			EvolutionLearningRule* learningRule = static_cast<EvolutionLearningRule*>(IOStorage<AbstractLearningRule>::pop());
			ar(cereal::base_class<AbstractEvolutionLearningRule>(learningRule));
			IOStorage<AbstractLearningRule>::push(learningRule);
		}
	};
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(EvolutionLearningRule);

#endif