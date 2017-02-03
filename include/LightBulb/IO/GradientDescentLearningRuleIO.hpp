#pragma once

#ifndef _GRADIENTDESCENTLEARNINGRULEIO_H_
#define _GRADIENTDESCENTLEARNINGRULEIO_H_

// Includes
#include "LightBulb/Learning/Supervised/GradientDescentLearningRule.hpp"
#include "LightBulb/IO/ConstructExisting.hpp"

namespace LightBulb
{
	/**
	* \brief Serializes a GradientDescentLearningRule.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param learningRule The GradientDescentLearningRule to serialize.
	*/
	template <class Archive>
	extern void serialize(Archive& archive, GradientDescentLearningRule& learningRule);
}


namespace cereal
{
	CONSTRUCT_EXISTING(LightBulb::GradientDescentLearningRule, LightBulb::AbstractLearningRule)
	{
		/**
		* \brief Constructs a existing GradientDescentLearningRule.
		* \tparam Archive The archive type.
		* \param ar The archive which should be used.
		* \param learningRule The existing GradientDescentLearningRule to construct.
		*/
		template <class Archive>
		static void construct(Archive& ar, LightBulb::GradientDescentLearningRule& learningRule);
	};
}

#endif