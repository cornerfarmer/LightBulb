#pragma once

#ifndef _BACKPROPAGATIONIO_H_
#define _BACKPROPAGATIONIO_H_

// Libary includes
#include "LightBulb/Learning/Supervised/GradientCalculation/Backpropagation.hpp"

namespace LightBulb
{
	/**
	* \brief Serializes Backpropagation.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param backpropagation The Backpropagation to serialize.
	*/
	template <class Archive>
	extern void serialize(Archive& archive, Backpropagation& backpropagation);
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
		static void construct(Archive& ar, LightBulb::Backpropagation& backpropagation);
	};
}

#include "LightBulb/IO/TemplateDeclaration.hpp"
CEREAL_FORCE_DYNAMIC_INIT_FIXED(Backpropagation)

#endif
