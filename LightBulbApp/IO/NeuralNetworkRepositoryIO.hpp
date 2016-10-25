#pragma once

#ifndef _NEURALNETWORKREPOSITORYIO_H_
#define _NEURALNETWORKREPOSITORYIO_H_

// Includes
#include "Repositories/NeuralNetworkRepository.hpp"
// Libraray includes
#include <cereal/cereal.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes a NeuralNetworkRepository.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param neuralNetworkRepository The NeuralNetworkRepository to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, NeuralNetworkRepository& neuralNetworkRepository)
	{
		archive(cereal::make_nvp("neuralNetworks", neuralNetworkRepository.neuralNetworks));
		neuralNetworkRepository.throwEvent(EVT_NN_CHANGED, neuralNetworkRepository);
	}
}

#endif