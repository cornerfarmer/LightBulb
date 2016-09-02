#pragma once

#ifndef _SIMPLEGRADIENTDECENTIO_H_
#define _SIMPLEGRADIENTDECENTIO_H_

// Libary includes
#include "Learning/Supervised/GradientDecentAlgorithms/SimpleGradientDecent.hpp"
#include "ConstructExisting.hpp"
#include "IO/MatrixIO.hpp"

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

template <class Archive>
void serialize(Archive& archive, SimpleGradientDecent& simpleGradientDecent)
{
	archive(cereal::base_class<AbstractGradientDecentAlgorithm>(&simpleGradientDecent));
	archive(cereal::make_nvp("previousDeltaWeights", simpleGradientDecent.previousDeltaWeights));
}


namespace cereal
{
	CONSTRUCT_EXISTING(SimpleGradientDecent, AbstractGradientDecentAlgorithm)
	{
		template <class Archive>
		static void construct(Archive& ar, SimpleGradientDecent& simpleGradientDecent)
		{
			ar(cereal::base_class<AbstractGradientDecentAlgorithm>(&simpleGradientDecent));
			ar(cereal::make_nvp("previousDeltaWeights", simpleGradientDecent.previousDeltaWeights));
		}
	};
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(SimpleGradientDecent);

#endif
