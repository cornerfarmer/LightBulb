#pragma once

#ifndef _LAYEREDNETWORKIO_H_
#define _LAYEREDNETWORKIO_H_

// Libary includes
#include "IO/MatrixIO.hpp"
#include <NetworkTopology/LayeredNetwork.hpp>
#include <NeuronFactory/AbstractNeuronDescriptionFactory.hpp>

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>



template <class Archive>
void save(Archive& archive, LayeredNetworkOptions const & options)
{
	archive(cereal::make_nvp("enableShortcuts", options.enableShortcuts));
	archive(cereal::make_nvp("neuronsPerLayerCount", options.neuronsPerLayerCount));
	archive(cereal::make_nvp("outputNeuronsIndices", options.outputNeuronsIndices));
	archive(cereal::make_nvp("useBiasNeuron", options.useBiasNeuron));

	std::unique_ptr<AbstractNeuronDescriptionFactory> descriptionFactory(options.descriptionFactory->getCopy());
	archive(cereal::make_nvp("descriptionFactory", descriptionFactory));
}

template <class Archive>
void load(Archive& archive, LayeredNetworkOptions& options)
{
	archive(cereal::make_nvp("enableShortcuts", options.enableShortcuts));
	archive(cereal::make_nvp("neuronsPerLayerCount", options.neuronsPerLayerCount));
	archive(cereal::make_nvp("outputNeuronsIndices", options.outputNeuronsIndices));
	archive(cereal::make_nvp("useBiasNeuron", options.useBiasNeuron));
	std::unique_ptr<AbstractNeuronDescriptionFactory> descriptionFactory;
	archive(cereal::make_nvp("descriptionFactory", descriptionFactory));
	options.descriptionFactory = descriptionFactory.release();
}


template <class Archive>
void save(Archive& archive, LayeredNetwork const & layeredNetwork)
{
	archive(cereal::make_nvp("options", layeredNetwork.options));
	archive(cereal::make_nvp("netInputs", layeredNetwork.netInputs));
	archive(cereal::make_nvp("activations", layeredNetwork.activations));
	archive(cereal::make_nvp("weights", layeredNetwork.weights));
}


template <class Archive>
void load(Archive& archive, LayeredNetwork & layeredNetwork)
{
	archive(cereal::make_nvp("options", layeredNetwork.options));
	layeredNetwork.buildNetwork();
	archive(cereal::make_nvp("netInputs", layeredNetwork.netInputs));
	archive(cereal::make_nvp("activations", layeredNetwork.activations));
	archive(cereal::make_nvp("weights", layeredNetwork.weights));
}



#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LayeredNetwork);

#endif
