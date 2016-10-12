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
	/**
	* \brief Serializes Backpropagation.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param backpropagation The Backpropagation to serialize.
	*/
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
		/**
		* \brief Constructs existing Backpropagation.
		* \tparam Archive The archive type.
		* \param ar The archive which should be used.
		* \param backpropagation The existing Backpropagation to construct.
		*/
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
