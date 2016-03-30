#pragma once

#ifndef _NEURALNETWORKREPOSITORY_H_
#define _NEURALNETWORKREPOSITORY_H_

// Library includes
#include <vector>
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>
#include <Event/Observable.hpp>

// Includes

// Forward declarations

enum NeuralNetworkRepositoryEvents
{
	EVT_NN_CHANGED
};

class NeuralNetworkRepository : public Observable<NeuralNetworkRepositoryEvents, NeuralNetworkRepository>
{
private:
	std::vector<AbstractNeuralNetwork*> neuralNetworks;
public:
	NeuralNetworkRepository();
	std::vector<AbstractNeuralNetwork*>* getNeuralNetworks();
	int getIndexOfNeuralNetwork(AbstractNeuralNetwork* network);
	void Add(AbstractNeuralNetwork* neuralNetwork);
};

#endif
