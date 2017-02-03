#pragma once

#ifndef _NEURALNETWORKREPOSITORYIO_H_
#define _NEURALNETWORKREPOSITORYIO_H_

// Includes
#include "LightBulbApp/Repositories/NeuralNetworkRepository.hpp"

namespace LightBulb
{
	/**
	* \brief Serializes a NeuralNetworkRepository.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param neuralNetworkRepository The NeuralNetworkRepository to serialize.
	*/
	template <class Archive>
	extern void serialize(Archive& archive, NeuralNetworkRepository& neuralNetworkRepository);
}

#endif