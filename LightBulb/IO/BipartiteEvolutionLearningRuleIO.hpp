#pragma once

#ifndef _BIPARTITEEVOLUTIONLEARNINGRULEIO_H_
#define _BIPARTITEEVOLUTIONLEARNINGRULEIO_H_

// Includes
#include "Learning/Evolution/BipartiteEvolutionLearningRule.hpp"
#include "IOStorage.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

template <class Archive>
void serialize(Archive& archive, BipartiteEvolutionLearningRule& learningRule)
{
	archive(cereal::base_class<AbstractEvolutionLearningRule>(&learningRule));

	std::unique_ptr<AbstractLearningRule> subLearningRule(learningRule.getOptions()->learningRule1);
	archive(cereal::make_nvp("learningRule1", subLearningRule));
	subLearningRule.release();

	subLearningRule.reset(learningRule.getOptions()->learningRule2);
	archive(cereal::make_nvp("learningRule2", subLearningRule));
	subLearningRule.release();
}

namespace cereal
{
	template <> struct LoadAndConstruct<BipartiteEvolutionLearningRule>
	{
		template <class Archive>
		static void load_and_construct(Archive& ar, cereal::construct<BipartiteEvolutionLearningRule>& construct)
		{
			BipartiteEvolutionLearningRule* learningRule = static_cast<BipartiteEvolutionLearningRule*>(IOStorage<AbstractLearningRule>::pop());
			ar(cereal::base_class<AbstractEvolutionLearningRule>(learningRule));

			IOStorage<AbstractLearningRule>::push(learningRule->getOptions()->learningRule1);
			std::unique_ptr<AbstractLearningRule> learningRuleDummy;
			ar(cereal::make_nvp("learningRule1", learningRuleDummy));
			learningRule->getOptions()->learningRule1 = static_cast<EvolutionLearningRule*>(IOStorage<AbstractLearningRule>::pop());

			IOStorage<AbstractLearningRule>::push(learningRule->getOptions()->learningRule2);
			ar(cereal::make_nvp("learningRule2", learningRuleDummy));
			learningRule->getOptions()->learningRule2 = static_cast<EvolutionLearningRule*>(IOStorage<AbstractLearningRule>::pop());

			IOStorage<AbstractLearningRule>::push(learningRule);
		}
	};
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(BipartiteEvolutionLearningRule);

#endif