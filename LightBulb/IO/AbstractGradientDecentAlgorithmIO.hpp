#pragma once

#ifndef _ABSTRACTGRADIENTDECENTALGORITHMIO_H_
#define _ABSTRACTGRADIENTDECENTALGORITHMIO_H_

// Includes
#include "Learning/Supervised/GradientDecentAlgorithms/AbstractGradientDecentAlgorithm.hpp"

// Libraray includes
#include <cereal/cereal.hpp>

namespace LightBulb
{
	template <class Archive>
	void serialize(Archive& archive, AbstractGradientDecentAlgorithm& gradientDecentAlgorithm)
	{
		archive(cereal::make_nvp("initialized", gradientDecentAlgorithm.initialized));
	}
}

#endif