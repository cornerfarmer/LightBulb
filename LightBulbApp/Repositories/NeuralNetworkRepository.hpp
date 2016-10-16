#pragma once

#ifndef _NEURALNETWORKREPOSITORY_H_
#define _NEURALNETWORKREPOSITORY_H_

// Library includes
#include <vector>
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>
#include <Event/Observable.hpp>
#include <memory>

// Includes

namespace LightBulb
{
	// Forward declarations

	enum NeuralNetworkRepositoryEvents
	{
		EVT_NN_CHANGED
	};

	class NeuralNetworkRepository : public LightBulb::Observable<NeuralNetworkRepositoryEvents, NeuralNetworkRepository>
	{
		template <class Archive>
		friend void serialize(Archive& archive, NeuralNetworkRepository& neuralNetworkRepository);
	private:
		std::vector<std::unique_ptr<AbstractNeuralNetwork>> neuralNetworks;
	public:
		NeuralNetworkRepository();
		const std::vector<std::unique_ptr<AbstractNeuralNetwork>>* getNeuralNetworks() const;
		int getIndexOfNeuralNetwork(const AbstractNeuralNetwork* network) const;
		void Add(AbstractNeuralNetwork* neuralNetwork);
		void save(const std::string& path, int neuralNetworkIndex) const;
		void load(const std::string& path);
	};
}

#include "IO/NeuralNetworkRepositoryIO.hpp"

#endif
