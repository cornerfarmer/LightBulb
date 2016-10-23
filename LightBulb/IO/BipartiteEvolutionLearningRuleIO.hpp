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

namespace LightBulb
{
	/**
	* \brief Serializes a BipartiteEvolutionLearningRule.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param learningRule The BipartiteEvolutionLearningRule to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, BipartiteEvolutionLearningRule& learningRule)
	{
		archive(cereal::base_class<AbstractEvolutionLearningRule>(&learningRule));

		std::unique_ptr<AbstractLearningRule> subLearningRule(learningRule.getOptions().learningRule1);
		archive(cereal::make_nvp("learningRule1", subLearningRule));
		subLearningRule.release();

		subLearningRule.reset(learningRule.getOptions().learningRule2);
		archive(cereal::make_nvp("learningRule2", subLearningRule));
		subLearningRule.release();
	}
}

namespace cereal
{
	template <> struct LoadAndConstruct<LightBulb::BipartiteEvolutionLearningRule>
	{
		/**
		* \brief Constructs a BipartiteEvolutionLearningRule.
		* \tparam Archive The archive type.
		* \param ar The archive which should be used.
		* \param construct The BipartiteEvolutionLearningRule construct object.
		*/
		template <class Archive>
		static void load_and_construct(Archive& ar, cereal::construct<LightBulb::BipartiteEvolutionLearningRule>& construct)
		{
			using namespace LightBulb;
			LightBulb::BipartiteEvolutionLearningRule* learningRule = static_cast<BipartiteEvolutionLearningRule*>(IOStorage<AbstractLearningRule>::pop());
			ar(cereal::base_class<AbstractEvolutionLearningRule>(learningRule));

			LightBulb::IOStorage<LightBulb::AbstractLearningRule>::push(learningRule->getOptions().learningRule1);
			std::unique_ptr<LightBulb::AbstractLearningRule> learningRuleDummy;
			ar(cereal::make_nvp("learningRule1", learningRuleDummy));
			static_cast<BipartiteEvolutionLearningRuleOptions*>(learningRule->options.get())->learningRule1 = static_cast<LightBulb::AbstractEvolutionLearningRule*>(IOStorage<AbstractLearningRule>::pop());

			LightBulb::IOStorage<LightBulb::AbstractLearningRule>::push(learningRule->getOptions().learningRule2);
			ar(cereal::make_nvp("learningRule2", learningRuleDummy));
			static_cast<BipartiteEvolutionLearningRuleOptions*>(learningRule->options.get())->learningRule2 = static_cast<LightBulb::AbstractEvolutionLearningRule*>(IOStorage<AbstractLearningRule>::pop());

			LightBulb::IOStorage<LightBulb::AbstractLearningRule>::push(learningRule);
		}
	};
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::BipartiteEvolutionLearningRule);

#endif