#pragma once

#ifndef _POLICYGRADIENTLEARNINGRULEIO_H_
#define _POLICYGRADIENTLEARNINGRULEIO_H_

// Includes
#include "LightBulb/Learning/Reinforcement/PolicyGradientLearningRule.hpp"
#include "LightBulb/IO/ConstructExisting.hpp"

namespace LightBulb
{
	/**
	* \brief Serializes a PolicyGradientLearningRule.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param learningRule The PolicyGradientLearningRule to serialize.
	*/
	template <class Archive>
	extern void serialize(Archive& archive, PolicyGradientLearningRule& learningRule);
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
		static void construct(Archive& ar, LightBulb::PolicyGradientLearningRule& learningRule);
	};
}

#endif