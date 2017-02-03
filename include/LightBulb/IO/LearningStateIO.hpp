#pragma once

#ifndef _LEARNINGSTATEIO_H_
#define _LEARNINGSTATEIO_H_

// Includes
#include "LightBulb/Learning/LearningState.hpp"

namespace LightBulb
{
	/**
	* \brief Serializes a LearningState.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param learningState The LearningState to serialize.
	*/
	template <class Archive>
	extern void serialize(Archive& archive, LearningState& learningState);
}

namespace cereal
{
	template <> struct LoadAndConstruct<LightBulb::LearningState>
	{
		/**
		* \brief Constructs a LearningState.
		* \tparam Archive The archive type.
		* \param ar The archive which should be used.
		* \param construct The LearningState construct object.
		*/
		template <class Archive>
		static void load_and_construct(Archive& ar, construct<LightBulb::LearningState>& construct);
	};
}

#endif
