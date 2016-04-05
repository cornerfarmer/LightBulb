#pragma once

#ifndef _IO_NEURALNETWORKIO_H_
#define _IO_NEURALNETWORKIO_H_

// Includes
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "IO/LayeredNetworkIO.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

template <class Archive>
void serialize(Archive& archive, NeuralNetwork& neuralNetwork)
{
	archive(cereal::make_nvp("networkTopology", neuralNetwork.networkTopology));
	archive(cereal::make_nvp("state", neuralNetwork.state));
}

namespace cereal
{
	template <> struct LoadAndConstruct<NeuralNetwork>
	{
		template <class Archive>
		static void load_and_construct(Archive& ar, cereal::construct<NeuralNetwork>& construct)
		{
			std::unique_ptr<AbstractNetworkTopology> networkTopology;
			ar(cereal::make_nvp("networkTopology", networkTopology));
			construct(networkTopology.release());
			ar(cereal::make_nvp("state", construct->state));
		}
	};
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(NeuralNetwork);

#endif