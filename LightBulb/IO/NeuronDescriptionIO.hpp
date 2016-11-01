#pragma once

#ifndef _NEURONDESCRIPTIONIO_H_
#define _NEURONDESCRIPTIONIO_H_

// Libary includes
#include <NeuronDescription/NeuronDescription.hpp>
#include "Function/ActivationFunction/IdentityFunction.hpp"
#include <cereal/cereal.hpp>
#include <cereal/access.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes a NeuronDescription.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param neuronDescription The NeuronDescription to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, NeuronDescription& neuronDescription)
	{
		archive(cereal::make_nvp("inputFunction", neuronDescription.inputFunction));
		archive(cereal::make_nvp("activationFunction", neuronDescription.activationFunction));
	}
}

namespace cereal
{
	template <> struct LoadAndConstruct<LightBulb::NeuronDescription>
	{
		/**
		* \brief Constructs a NeuronDescription.
		* \tparam Archive The archive type.
		* \param ar The archive which should be used.
		* \param construct The NeuronDescription construct object.
		*/
		template <class Archive>
		static void load_and_construct(Archive & ar, construct<LightBulb::NeuronDescription>& construct)
		{
			using namespace LightBulb;
			std::unique_ptr<AbstractInputFunction> inputFunction;
			ar(make_nvp("inputFunction", inputFunction));
			std::unique_ptr<AbstractActivationFunction> activationFunction;
			ar(make_nvp("activationFunction", activationFunction));
			construct(inputFunction.release(), activationFunction.release());
		}
	};
}

#endif
