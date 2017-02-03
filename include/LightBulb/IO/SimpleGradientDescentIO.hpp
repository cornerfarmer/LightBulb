#pragma once

#ifndef _SIMPLEGRADIENTDESCENTIO_H_
#define _SIMPLEGRADIENTDESCENTIO_H_

// Libary includes
#include "LightBulb/Learning/Supervised/GradientDescentAlgorithms/SimpleGradientDescent.hpp"
#include "LightBulb/IO/ConstructExisting.hpp"

namespace LightBulb
{
	/**
	* \brief Serializes SimpleGradientDescent.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param simpleGradientDescent The SimpleGradientDescent to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, SimpleGradientDescent& simpleGradientDescent);
}

namespace cereal
{
	CONSTRUCT_EXISTING(LightBulb::SimpleGradientDescent, LightBulb::AbstractGradientDescentAlgorithm)
	{
		/**
		* \brief Constructs a existing SimpleGradientDescent.
		* \tparam Archive The archive type.
		* \param ar The archive which should be used.
		* \param simpleGradientDescent The existing SimpleGradientDescent to construct.
		*/
		template <class Archive>
		static void construct(Archive& ar, LightBulb::SimpleGradientDescent& simpleGradientDescent);
	};
}

#endif
