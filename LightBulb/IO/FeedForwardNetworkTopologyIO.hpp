#pragma once

#ifndef _FEEDFORWARDNETWORKTOPOLOGYIO_H_
#define _FEEDFORWARDNETWORKTOPOLOGYIO_H_

// Libary includes
#include "IO/MatrixIO.hpp"
#include <NetworkTopology/FeedForwardNetworkTopology.hpp>
#include <NeuronDescription/AbstractNeuronDescriptionFactory.hpp>

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>

namespace LightBulb
{

	template <class Archive>
	void save(Archive& archive, FeedForwardNetworkTopologyOptions const & options)
	{
		archive(cereal::make_nvp("enableShortcuts", options.enableShortcuts));
		archive(cereal::make_nvp("neuronsPerLayerCount", options.neuronsPerLayerCount));
		archive(cereal::make_nvp("useBiasNeuron", options.useBiasNeuron));

		std::unique_ptr<AbstractNeuronDescriptionFactory> descriptionFactory(options.descriptionFactory->getCopy());
		archive(cereal::make_nvp("descriptionFactory", descriptionFactory));
	}

	template <class Archive>
	void load(Archive& archive, FeedForwardNetworkTopologyOptions& options)
	{
		archive(cereal::make_nvp("enableShortcuts", options.enableShortcuts));
		archive(cereal::make_nvp("neuronsPerLayerCount", options.neuronsPerLayerCount));
		archive(cereal::make_nvp("useBiasNeuron", options.useBiasNeuron));
		std::unique_ptr<AbstractNeuronDescriptionFactory> descriptionFactory;
		archive(cereal::make_nvp("descriptionFactory", descriptionFactory));
		options.descriptionFactory = descriptionFactory.release();
	}


	template <class Archive>
	void save(Archive& archive, FeedForwardNetworkTopology const & FeedForwardNetworkTopology)
	{
		archive(cereal::make_nvp("options", FeedForwardNetworkTopology.options));
		archive(cereal::make_nvp("netInputs", FeedForwardNetworkTopology.netInputs));
		archive(cereal::make_nvp("activations", FeedForwardNetworkTopology.activations));
		archive(cereal::make_nvp("weights", FeedForwardNetworkTopology.weights));
	}


	template <class Archive>
	void load(Archive& archive, FeedForwardNetworkTopology & FeedForwardNetworkTopology)
	{
		archive(cereal::make_nvp("options", FeedForwardNetworkTopology.options));
		FeedForwardNetworkTopology.buildNetwork();
		archive(cereal::make_nvp("netInputs", FeedForwardNetworkTopology.netInputs));
		archive(cereal::make_nvp("activations", FeedForwardNetworkTopology.activations));
		archive(cereal::make_nvp("weights", FeedForwardNetworkTopology.weights));
		for (int l = 0; l < FeedForwardNetworkTopology.getLayerCount(); l++)
			FeedForwardNetworkTopology.rebuildActivationsPerLayer(l);
	}

}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::FeedForwardNetworkTopology);

#endif
