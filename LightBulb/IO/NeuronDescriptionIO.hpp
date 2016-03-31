#pragma once

#ifndef _NEURONDESCRIPTIONIO_H_
#define _NEURONDESCRIPTIONIO_H_

// Libary includes
#include "IO/WeightedSumFunctionIO.hpp"
#include "IO/FermiFunctionIO.hpp"
#include <Neuron/NeuronDescription.hpp>
#include <cereal/cereal.hpp>
#include <cereal/access.hpp>

template <class Archive>
void serialize(Archive& archive, NeuronDescription& neuronDescription)
{
	archive(CEREAL_NVP(neuronDescription.inputFunction));
	archive(CEREAL_NVP(neuronDescription.activationFunction));
}

namespace cereal
{
	template <> struct LoadAndConstruct<NeuronDescription>
	{
		template <class Archive>
		static void load_and_construct(Archive & ar, cereal::construct<NeuronDescription>& construct)
		{
			std::unique_ptr<AbstractInputFunction> inputFunction;
			ar(inputFunction);
			std::unique_ptr<AbstractActivationFunction> activationFunction;
			ar(activationFunction);
			construct(inputFunction.release(), activationFunction.release());
		}
	};
}

#endif
