#pragma once

#ifndef _IO_NEURALNETWORKIO_H_
#define _IO_NEURALNETWORKIO_H_

// Includes
#include "NeuralNetwork/NeuralNetwork.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes a NeuralNetwork.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param neuralNetwork The NeuralNetwork to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, NeuralNetwork& neuralNetwork)
	{
		archive(cereal::make_nvp("networkTopology", neuralNetwork.networkTopology));
		archive(cereal::make_nvp("state", static_cast<int>(neuralNetwork.state)));
		archive(cereal::make_nvp("name", neuralNetwork.name));
	}
}

namespace cereal
{
	template <> struct LoadAndConstruct<LightBulb::NeuralNetwork>
	{
		/**
		* \brief Constructs a NeuralNetwork.
		* \tparam Archive The archive type.
		* \param ar The archive which should be used.
		* \param construct The NeuralNetwork construct object.
		*/
		template <class Archive>
		static void load_and_construct(Archive& ar, construct<LightBulb::NeuralNetwork>& construct)
		{
			using namespace LightBulb;
			std::unique_ptr<AbstractNetworkTopology> networkTopology;
			ar(make_nvp("networkTopology", networkTopology));
			construct(networkTopology.release());
			ar(make_nvp("state", construct->state));
			ar(make_nvp("name", construct->name));
		}
	};
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::NeuralNetwork);

#endif