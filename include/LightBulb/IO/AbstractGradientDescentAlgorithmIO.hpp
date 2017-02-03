#pragma once

#ifndef _ABSTRACTGRADIENTDESCENTALGORITHMIO_H_
#define _ABSTRACTGRADIENTDESCENTALGORITHMIO_H_

// Includes
#include "LightBulb/Learning/Supervised/GradientDescentAlgorithms/AbstractGradientDescentAlgorithm.hpp"

namespace LightBulb
{
	/**
	* \brief Serializes an AbstractGradientDescentAlgorithm
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param gradientDescentAlgorithm The AbstractGradientDescentAlgorithm to serialize.
	*/
	template <class Archive>
	extern void serialize(Archive& archive, AbstractGradientDescentAlgorithm& gradientDescentAlgorithm);
}

#endif