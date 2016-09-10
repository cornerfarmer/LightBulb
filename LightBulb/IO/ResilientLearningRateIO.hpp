#pragma once

#ifndef _RESILIENTLEARNINGRATEIO_H_
#define _RESILIENTLEARNINGRATEIO_H_

// Libary includes
#include "Learning/Supervised/GradientDecentAlgorithms/ResilientLearningRate.hpp"
#include "ConstructExisting.hpp"
#include "IO/MatrixIO.hpp"

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

namespace LightBulb
{
	template <class Archive>
	void serialize(Archive& archive, ResilientLearningRate & resilientLearningRate)
	{
		archive(cereal::base_class<AbstractGradientDecentAlgorithm>(&resilientLearningRate));
		archive(cereal::make_nvp("previousLearningRates", resilientLearningRate.previousLearningRates));
	}
}

namespace cereal
{
	CONSTRUCT_EXISTING(LightBulb::ResilientLearningRate, LightBulb::AbstractGradientDecentAlgorithm)
	{
		template <class Archive>
		static void construct(Archive& ar, LightBulb::ResilientLearningRate & resilientLearningRate)
		{
			ar(cereal::base_class<LightBulb::AbstractGradientDecentAlgorithm>(&resilientLearningRate));
			ar(cereal::make_nvp("previousLearningRates", resilientLearningRate.previousLearningRates));
		}
	};
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::ResilientLearningRate);

#endif
