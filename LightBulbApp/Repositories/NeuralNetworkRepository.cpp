// Includes
#include "NeuralNetworkRepository.hpp"
#include <fstream>
#include <cereal/archives/xml.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>
#include <IO/NeuralNetworkIO.hpp>

NeuralNetworkRepository::NeuralNetworkRepository()
{

}

std::vector<std::unique_ptr<AbstractNeuralNetwork>>* NeuralNetworkRepository::getNeuralNetworks()
{
	return &neuralNetworks;
}

int NeuralNetworkRepository::getIndexOfNeuralNetwork(AbstractNeuralNetwork* network)
{
	for (int i = 0; i < neuralNetworks.size(); i++)
	{
		if (neuralNetworks[i].get() == network)
			return i;
	}
	return -1;
}

void NeuralNetworkRepository::Add(AbstractNeuralNetwork* neuralNetwork)
{
	neuralNetworks.push_back(std::unique_ptr<AbstractNeuralNetwork>(neuralNetwork));
	throwEvent(EVT_NN_CHANGED, this);
}

void NeuralNetworkRepository::save(std::string path, int neuralNetworkIndex)
{
	std::ofstream os(path);
	cereal::XMLOutputArchive archive(os);

	archive(neuralNetworks[neuralNetworkIndex]);
}
