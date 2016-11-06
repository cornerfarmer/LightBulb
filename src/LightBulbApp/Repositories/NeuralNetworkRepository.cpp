// Includes
#include "NeuralNetworkRepository.hpp"
#include <fstream>
#include "IO/UsedArchives.hpp"
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>

namespace LightBulb
{
	NeuralNetworkRepository::NeuralNetworkRepository()
	{

	}

	const std::vector<std::unique_ptr<AbstractNeuralNetwork>>& NeuralNetworkRepository::getNeuralNetworks() const
	{
		return neuralNetworks;
	}

	int NeuralNetworkRepository::getIndexOfNeuralNetwork(const AbstractNeuralNetwork& network) const
	{
		for (int i = 0; i < neuralNetworks.size(); i++)
		{
			if (neuralNetworks[i].get() == &network)
				return i;
		}
		return -1;
	}

	void NeuralNetworkRepository::Add(AbstractNeuralNetwork* neuralNetwork)
	{
		neuralNetworks.push_back(std::unique_ptr<AbstractNeuralNetwork>(neuralNetwork));
		throwEvent(EVT_NN_CHANGED, *this);
	}

	void NeuralNetworkRepository::save(const std::string& path, int neuralNetworkIndex) const
	{
		std::ofstream os(path);
		cereal::XMLOutputArchive archive(os);

		archive(neuralNetworks[neuralNetworkIndex]);
	}

	void NeuralNetworkRepository::load(const std::string& path)
	{
		std::ifstream is(path);
		cereal::XMLInputArchive archive(is);

		neuralNetworks.push_back(std::unique_ptr<AbstractNeuralNetwork>());
		archive(neuralNetworks.back());

		throwEvent(EVT_NN_CHANGED, *this);
	}
}