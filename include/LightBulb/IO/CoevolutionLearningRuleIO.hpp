#pragma once

#ifndef _COEVOLUTIONLEARNINGRULEIO_H_
#define _COEVOLUTIONLEARNINGRULEIO_H_

// Includes
#include "LightBulb/Learning/Evolution/CoevolutionLearningRule.hpp"
#include "LightBulb/IO/IOStorage.hpp"
#include "LightBulb/IO/ConstructExisting.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes a CoevolutionLearningRule.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param learningRule The CoevolutionLearningRule to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, CoevolutionLearningRule& learningRule)
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
	CONSTRUCT_EXISTING(LightBulb::CoevolutionLearningRule, LightBulb::AbstractLearningRule)
	{
		/**
		* \brief Constructs an existing CoevolutionLearningRule.
		* \tparam Archive The archive type.
		* \param ar The archive which should be used.
		* \param learningRule The existing EvolutionLearningRule to construct.
		*/
		template <class Archive>
		static void construct(Archive& ar, LightBulb::CoevolutionLearningRule& learningRule)
		{
			using namespace LightBulb;
			ar(base_class<AbstractEvolutionLearningRule>(&learningRule));

			IOStorage<AbstractLearningRule>::push(learningRule.getOptions().learningRule1);
			std::unique_ptr<AbstractLearningRule> learningRuleDummy;
			ar(make_nvp("learningRule1", learningRuleDummy));
			static_cast<CoevolutionLearningRuleOptions*>(learningRule.options.get())->learningRule1 = static_cast<AbstractEvolutionLearningRule*>(IOStorage<AbstractLearningRule>::pop());

			IOStorage<AbstractLearningRule>::push(learningRule.getOptions().learningRule2);
			ar(make_nvp("learningRule2", learningRuleDummy));
			static_cast<CoevolutionLearningRuleOptions*>(learningRule.options.get())->learningRule2 = static_cast<AbstractEvolutionLearningRule*>(IOStorage<AbstractLearningRule>::pop());
		}
	};
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::CoevolutionLearningRule);

#endif