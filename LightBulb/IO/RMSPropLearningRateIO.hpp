#pragma once

#ifndef _RMSPROPLEARNINGRATEIO_H_
#define _RMSPROPLEARNINGRATEIO_H_

// Libary includes
#include "Learning/Supervised/GradientDecentAlgorithms/RMSPropLearningRate.hpp"
#include "ConstructExisting.hpp"
#include "IO/MatrixIO.hpp"

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

namespace LightBulb
{
	template <class Archive>
	void serialize(Archive& archive, RMSPropLearningRate& rmsPropLearningRate)
	{
		archive(cereal::base_class<AbstractGradientDecentAlgorithm>(&rmsPropLearningRate));
		archive(cereal::make_nvp("prevDeltaWeights", rmsPropLearningRate.prevDeltaWeights));
		archive(cereal::make_nvp("prevGradient", rmsPropLearningRate.prevGradient));
		archive(cereal::make_nvp("prevSquaredGradient", rmsPropLearningRate.prevSquaredGradient));
	}
}

namespace cereal
{
	CONSTRUCT_EXISTING(LightBulb::RMSPropLearningRate, LightBulb::AbstractGradientDecentAlgorithm)
	{
		template <class Archive>
		static void construct(Archive& ar, LightBulb::RMSPropLearningRate& rmsPropLearningRate)
		{
			using namespace LightBulb;
			ar(cereal::base_class<AbstractGradientDecentAlgorithm>(&rmsPropLearningRate));
			ar(cereal::make_nvp("prevDeltaWeights", rmsPropLearningRate.prevDeltaWeights));
			ar(cereal::make_nvp("prevGradient", rmsPropLearningRate.prevGradient));
			ar(cereal::make_nvp("prevSquaredGradient", rmsPropLearningRate.prevSquaredGradient));
		}
	};
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::RMSPropLearningRate);

#endif
