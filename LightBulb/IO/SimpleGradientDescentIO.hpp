#pragma once

#ifndef _SIMPLEGRADIENTDESCENTIO_H_
#define _SIMPLEGRADIENTDESCENTIO_H_

// Libary includes
#include "Learning/Supervised/GradientDescentAlgorithms/SimpleGradientDescent.hpp"
#include "ConstructExisting.hpp"
#include "IO/MatrixIO.hpp"

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes SimpleGradientDescent.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param simpleGradientDescent The SimpleGradientDescent to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, SimpleGradientDescent& simpleGradientDescent)
	{
		archive(cereal::base_class<AbstractGradientDescentAlgorithm>(&simpleGradientDescent));
		archive(cereal::make_nvp("previousDeltaWeights", simpleGradientDescent.previousDeltaWeights));
	}
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
		static void construct(Archive& ar, LightBulb::SimpleGradientDescent& simpleGradientDescent)
		{
			using namespace LightBulb;
			ar(cereal::base_class<AbstractGradientDescentAlgorithm>(&simpleGradientDescent));
			ar(cereal::make_nvp("previousDeltaWeights", simpleGradientDescent.previousDeltaWeights));
		}
	};
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::SimpleGradientDescent);

#endif
