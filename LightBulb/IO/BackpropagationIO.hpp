#pragma once

#ifndef _BACKPROPAGATIONIO_H_
#define _BACKPROPAGATIONIO_H_

// Libary includes
#include "Learning/Supervised/GradientCalculation/Backpropagation.hpp"
#include "IO/MatrixIO.hpp"

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

template <class Archive>
void serialize(Archive& archive, Backpropagation& backpropagation)
{
	archive(cereal::base_class<AbstractGradientCalculation>(&backpropagation));
	archive(cereal::make_nvp("lastDeltaVectorOutputLayer", backpropagation.lastDeltaVectorOutputLayer));
}


namespace cereal
{
	CONSTRUCT_EXISTING(Backpropagation, AbstractGradientCalculation)
	{
		template <class Archive>
		static void construct(Archive& ar, Backpropagation& backpropagation)
		{
			ar(cereal::base_class<AbstractGradientCalculation>(&backpropagation));
			ar(cereal::make_nvp("lastDeltaVectorOutputLayer", backpropagation.lastDeltaVectorOutputLayer));
		}
	};
}


#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(Backpropagation);

#endif