#pragma once

#ifndef _ABSTRACTGRADIENTDESCENTALGORITHMIO_H_
#define _ABSTRACTGRADIENTDESCENTALGORITHMIO_H_

// Includes
#include "Learning/Supervised/GradientDescentAlgorithms/AbstractGradientDescentAlgorithm.hpp"

// Libraray includes
#include <cereal/cereal.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes an AbstractGradientDescentAlgorithm
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param gradientDescentAlgorithm The AbstractGradientDescentAlgorithm to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, AbstractGradientDescentAlgorithm& gradientDescentAlgorithm)
	{
		archive(cereal::make_nvp("initialized", gradientDescentAlgorithm.initialized));
	}
}

#endif