#pragma once

#ifndef _LAYEREDNETWORKIO_H_
#define _LAYEREDNETWORKIO_H_

// Libary includes
#include "IO/SameNeuronDescriptionFactoryIO.hpp"
#include "IO/DifferentNeuronDescriptionFactoryIO.hpp"
#include "IO/MatrixIO.hpp"
#include <NetworkTopology/LayeredNetwork.hpp>
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>


template <class Archive>
void serialize(Archive& archive, LayeredNetworkOptions& options)
{
	archive(CEREAL_NVP(options.enableShortcuts));
	archive(CEREAL_NVP(options.neuronsPerLayerCount));
	archive(CEREAL_NVP(options.outputNeuronsIndices));
	archive(CEREAL_NVP(options.useBiasNeuron));
	std::unique_ptr<AbstractNeuronDescriptionFactory> descriptionFactory(options.descriptionFactory->getCopy());
	archive(cereal::make_nvp("descriptionFactory", descriptionFactory));
}


template <class Archive>
void serialize(Archive& archive, LayeredNetwork& layeredNetwork)
{
	archive(CEREAL_NVP(layeredNetwork.options));
	archive(CEREAL_NVP(layeredNetwork.netInputs));
	archive(CEREAL_NVP(layeredNetwork.activations));
	archive(CEREAL_NVP(layeredNetwork.weights));
}

namespace cereal
{
	template <> struct LoadAndConstruct<LayeredNetwork>
	{
		template <class Archive>
		static void load_and_construct(Archive & ar, cereal::construct<LayeredNetwork> & construct)
		{
			LayeredNetworkOptions options;
			construct(options);
		}
	};
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LayeredNetwork);

#endif
