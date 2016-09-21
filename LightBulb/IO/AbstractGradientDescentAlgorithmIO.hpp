#pragma once

#ifndef _ABSTRACTGRADIENTDESCENTALGORITHMIO_H_
#define _ABSTRACTGRADIENTDESCENTALGORITHMIO_H_

// Includes
#include "Learning/Supervised/GradientDescentAlgorithms/AbstractGradientDescentAlgorithm.hpp"

// Libraray includes
#include <cereal/cereal.hpp>

namespace LightBulb
{
	template <class Archive>
	void serialize(Archive& archive, AbstractGradientDescentAlgorithm& gradientDescentAlgorithm)
	{
		archive(cereal::make_nvp("initialized", gradientDescentAlgorithm.initialized));
	}
}

#endif