// Includes
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "ActivationOrder/AbstractActivationOrder.hpp"
#include "NeuralNetwork/NeuralNetworkIO.hpp"
// Library includes
#include <exception>
#include <ctime>

namespace LightBulb
{
	NeuralNetwork::NeuralNetwork(AbstractNetworkTopology* networkTopology_)
	{
		// Check if all given options are correct
		if (!networkTopology_)
			throw std::invalid_argument("The given networkTopology is not valid");

		networkTopology.reset(networkTopology_);

		state = NN_STATE_READY;

		name = "NoName";

		creationTime = time(nullptr);
	}
	
	void NeuralNetwork::calculate(const std::vector<double>& input, std::vector<double>& output, const AbstractActivationOrder &activationOrder, bool resetActivations)
	{
		// If the calculation start at time 0
		if (resetActivations)
		{
			// Reset all activations
			networkTopology->resetActivation();
		}

		// Set the input into the neural network
		networkTopology->setInput(input);

		// Pass the work to the activationOrder
		activationOrder.executeActivation(*networkTopology);

		// Extract the output and save it into the output value
		networkTopology->getOutput(output);
	}

	AbstractNetworkTopology& NeuralNetwork::getNetworkTopology() const
	{
		return *networkTopology.get();
	}

	const std::string& NeuralNetwork::getName() const
	{
		return name;
	}

	const time_t& NeuralNetwork::getCreationDate() const
	{
		return creationTime;
	}

	const NeuralNetworkState& NeuralNetwork::getState() const
	{
		return state;
	}

	void NeuralNetwork::setState(NeuralNetworkState newState)
	{
		state = newState;
	}

	AbstractNeuralNetwork* NeuralNetwork::clone() const
	{
		NeuralNetwork* clone = new NeuralNetwork(networkTopology->clone());
		clone->name = name + " - clone";
		return clone;
	}

	void NeuralNetwork::setName(const std::string& name_)
	{
		name = name_;
	}
}