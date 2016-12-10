#pragma once

#ifndef _POLICYGRADIENTLEARNINGRULEIO_H_
#define _POLICYGRADIENTLEARNINGRULEIO_H_

// Includes
#include "LightBulb/Learning/Reinforcement/PolicyGradientLearningRule.hpp"
#include "LightBulb/IO/MatrixIO.hpp"
#include "LightBulb/IO/ConstructExisting.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes a PolicyGradientLearningRule.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param learningRule The PolicyGradientLearningRule to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, PolicyGradientLearningRule& learningRule)
	{
		archive(cereal::base_class<AbstractReinforcementLearningRule>(&learningRule));
		archive(cereal::make_nvp("valueFunctionNetwork", learningRule.valueFunctionNetwork));
	}
}


namespace cereal
{
	CONSTRUCT_EXISTING(LightBulb::PolicyGradientLearningRule, LightBulb::AbstractLearningRule)
	{
		/**
		* \brief Constructs a existing PolicyGradientLearningRule.
		* \tparam Archive The archive type.
		* \param ar The archive which should be used.
		* \param learningRule The existing PolicyGradientLearningRule to construct.
		*/
		template <class Archive>
		static void construct(Archive& ar, LightBulb::PolicyGradientLearningRule& learningRule)
		{
			using namespace LightBulb;
			ar(base_class<AbstractReinforcementLearningRule>(&learningRule));
			ar(cereal::make_nvp("valueFunctionNetwork", learningRule.valueFunctionNetwork));
		}
	};
}


#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::PolicyGradientLearningRule);

#endif