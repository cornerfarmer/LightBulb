#pragma once

#ifndef _RESILIENTLEARNINGRATEIO_H_
#define _RESILIENTLEARNINGRATEIO_H_

// Libary includes
#include "LightBulb/Learning/Supervised/GradientDescentAlgorithms/ResilientLearningRate.hpp"
#include "LightBulb/IO/ConstructExisting.hpp"
#include "LightBulb/IO/EigenMatrixIO.hpp"

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes a ResilientLearningRate.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param resilientLearningRate The ResilientLearningRate to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, ResilientLearningRate & resilientLearningRate)
	{
		archive(cereal::base_class<AbstractGradientDescentAlgorithm>(&resilientLearningRate));
		archive(cereal::make_nvp("previousLearningRates", resilientLearningRate.previousLearningRates));
	}
}

namespace cereal
{
	CONSTRUCT_EXISTING(LightBulb::ResilientLearningRate, LightBulb::AbstractGradientDescentAlgorithm)
	{
		/**
		* \brief Constructs a existing ResilientLearningRate.
		* \tparam Archive The archive type.
		* \param ar The archive which should be used.
		* \param resilientLearningRate The existing ResilientLearningRate to construct.
		*/
		template <class Archive>
		static void construct(Archive& ar, LightBulb::ResilientLearningRate & resilientLearningRate)
		{
			ar(base_class<LightBulb::AbstractGradientDescentAlgorithm>(&resilientLearningRate));
			ar(make_nvp("previousLearningRates", resilientLearningRate.previousLearningRates));
		}
	};
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::ResilientLearningRate);

#endif
