// Includes
#include "NeuralNetworkRepository.hpp"

NeuralNetworkRepository::NeuralNetworkRepository()
{

}

std::vector<AbstractNeuralNetwork*>* NeuralNetworkRepository::getNeuralNetworks()
{
	return &neuralNetworks;
}

int NeuralNetworkRepository::getIndexOfNeuralNetwork(AbstractNeuralNetwork* network)
{
	for (int i = 0; i < neuralNetworks.size(); i++)
	{
		if (neuralNetworks[i] == network)
			return i;
	}
	return -1;
}

void NeuralNetworkRepository::Add(AbstractNeuralNetwork* neuralNetwork)
{
	neuralNetworks.push_back(neuralNetwork);
	throwEvent(EVT_NN_CHANGED, this);
}
