// Includes
#include "NeuralNetwork/AbstractNeuralNetwork.hpp"

namespace LightBulb
{
	std::string AbstractNeuralNetwork::getStateAsString() const
	{
		if (getState() == NN_STATE_READY)
			return "ready";
		else if (getState() == NN_STATE_TRAINED)
			return "trained";
		else
			return "";
	}
}