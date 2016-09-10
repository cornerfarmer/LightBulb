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
		template <class Archive>
		static void load_and_construct(Archive & ar, cereal::construct<LightBulb::NeuronDescription>& construct)
		{
			using namespace LightBulb;
			std::unique_ptr<AbstractInputFunction> inputFunction;
			ar(cereal::make_nvp("inputFunction", inputFunction));
			std::unique_ptr<AbstractActivationFunction> activationFunction;
			ar(cereal::make_nvp("activationFunction", activationFunction));
			construct(inputFunction.release(), activationFunction.release());
		}
	};
}

#endif
