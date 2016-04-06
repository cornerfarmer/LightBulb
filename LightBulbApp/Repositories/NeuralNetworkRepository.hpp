#pragma once

#ifndef _NEURALNETWORKREPOSITORY_H_
#define _NEURALNETWORKREPOSITORY_H_

// Library includes
#include <vector>
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>
#include <Event/Observable.hpp>
#include <memory>

// Includes

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
	std::vector<std::unique_ptr<AbstractNeuralNetwork>>* getNeuralNetworks();
	int getIndexOfNeuralNetwork(AbstractNeuralNetwork* network);
	void Add(AbstractNeuralNetwork* neuralNetwork);
	void save(std::string path, int neuralNetworkIndex);
	void load(std::string path);
};

#endif
