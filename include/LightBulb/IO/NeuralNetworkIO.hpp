#pragma once

#ifndef _IO_NEURALNETWORKIO_H_
#define _IO_NEURALNETWORKIO_H_

// Includes
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"

namespace LightBulb
{
	/**
	* \brief Serializes a NeuralNetwork.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param neuralNetwork The NeuralNetwork to serialize.
	*/
	template <class Archive>
	extern void serialize(Archive& archive, NeuralNetwork& neuralNetwork);
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
		static void load_and_construct(Archive& ar, construct<LightBulb::NeuralNetwork>& construct);
	};
}

#endif