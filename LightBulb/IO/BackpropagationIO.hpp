#pragma once

#ifndef _BACKPROPAGATIONIO_H_
#define _BACKPROPAGATIONIO_H_

// Libary includes
#include "Learning/Supervised/GradientCalculation/Backpropagation.hpp"
#include "IO/MatrixIO.hpp"

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

namespace LightBulb
{
	template <class Archive>
	void serialize(Archive& archive, Backpropagation& backpropagation)
	{
		archive(cereal::base_class<AbstractGradientCalculation>(&backpropagation));
		archive(cereal::make_nvp("lastDeltaVectorOutputLayer", backpropagation.lastDeltaVectorOutputLayer));
	}
}

namespace cereal
{
	CONSTRUCT_EXISTING(LightBulb::Backpropagation, LightBulb::AbstractGradientCalculation)
	{
		template <class Archive>
		static void construct(Archive& ar, LightBulb::Backpropagation& backpropagation)
		{
			ar(cereal::base_class<LightBulb::AbstractGradientCalculation>(&backpropagation));
			ar(cereal::make_nvp("lastDeltaVectorOutputLayer", backpropagation.lastDeltaVectorOutputLayer));
		}
	};
}


#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::Backpropagation);

#endif
