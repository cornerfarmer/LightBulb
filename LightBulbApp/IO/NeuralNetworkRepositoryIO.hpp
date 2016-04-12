#pragma once

#ifndef _NEURALNETWORKREPOSITORYIO_H_
#define _NEURALNETWORKREPOSITORYIO_H_

// Includes
#include "Repositories/NeuralNetworkRepository.hpp"
// Libraray includes
#include <cereal/cereal.hpp>

template <class Archive>
void serialize(Archive& archive, NeuralNetworkRepository& neuralNetworkRepository)
{
	archive(cereal::make_nvp("neuralNetworks", neuralNetworkRepository.neuralNetworks));
	neuralNetworkRepository.throwEvent(EVT_NN_CHANGED, &neuralNetworkRepository);
}


#endif