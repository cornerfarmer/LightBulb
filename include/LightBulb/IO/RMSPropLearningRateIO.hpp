#pragma once

#ifndef _RMSPROPLEARNINGRATEIO_H_
#define _RMSPROPLEARNINGRATEIO_H_

// Libary includes
#include "LightBulb/Learning/Supervised/GradientDescentAlgorithms/RMSPropLearningRate.hpp"
#include "LightBulb/IO/ConstructExisting.hpp"

namespace LightBulb
{
	/**
	* \brief Serializes a RMSPropLearningRate.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param rmsPropLearningRate The RMSPropLearningRate to serialize.
	*/
	template <class Archive>
	extern void serialize(Archive& archive, RMSPropLearningRate& rmsPropLearningRate);
}

namespace cereal
{
	CONSTRUCT_EXISTING(LightBulb::RMSPropLearningRate, LightBulb::AbstractGradientDescentAlgorithm)
	{
		/**
		* \brief Constructs a existing RMSPropLearningRate.
		* \tparam Archive The archive type.
		* \param ar The archive which should be used.
		* \param rmsPropLearningRate The existing RMSPropLearningRate to construct.
		*/
		template <class Archive>
		static void construct(Archive& ar, LightBulb::RMSPropLearningRate& rmsPropLearningRate);
	};
}

#include "LightBulb/IO/TemplateDeclaration.hpp"
CEREAL_FORCE_DYNAMIC_INIT_FIXED(RMSPropLearningRate)

#endif
