// Includes
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "ActivationOrder/AbstractActivationOrder.hpp"
#include "NeuralNetwork/NeuralNetworkIO.hpp"
// Library includes
#include <exception>
#include <ctime>

NeuralNetwork::NeuralNetwork(AbstractNetworkTopology* networkTopology_)
{
	// Check if all given options are correct
	if (!networkTopology_)
		throw std::invalid_argument("The given networkTopology is not valid");

	networkTopology.reset(networkTopology_);

	state = NN_STATE_READY;
}

void NeuralNetwork::calculate(std::vector<std::vector<double>>& input, std::vector<std::vector<double>>& output, AbstractActivationOrder &activationOrder, int startTime, int timeStepCount, std::vector<std::map<AbstractNeuron*, double>>* outputValuesInTime, std::vector<std::map<AbstractNeuron*, double>>* netInputValuesInTime, bool resetActivations)
{
	// If the calculation start at time 0
	if (startTime == 0 && resetActivations)
	{
		// Reset all activations
		networkTopology->resetActivation();
	}

	// Do for every time step
	for (int timeStep = startTime; (timeStep < input.size() && timeStepCount == -1) || timeStep - startTime < timeStepCount; timeStep++)
	{
		// Set the input into the neural network
		if (input[timeStep].size() > 0)
			networkTopology->setInput(input[timeStep]);

		// Pass the work to the activationOrder
		activationOrder.executeActivation(*networkTopology);

		// Extract the output and save it into the output value
		networkTopology->getOutput(output[timeStep]);

		// If the output values map is not null, fill it with all current output values 
		if (outputValuesInTime != NULL)
			networkTopology->getAllNeuronOutputs((*outputValuesInTime)[timeStep]);
		// If the netInput values map is not null, fill it with all current netInput values 
		if (netInputValuesInTime != NULL)
			networkTopology->getAllNeuronNetInputs((*netInputValuesInTime)[timeStep]);
	}

}

void NeuralNetwork::calculate(std::vector<double>& input, std::vector<double>& output, AbstractActivationOrder &activationOrder, bool resetActivations)
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

AbstractNetworkTopology* NeuralNetwork::getNetworkTopology()
{
	return networkTopology.get();
}

std::string NeuralNetwork::getName()
{
	return "MyName";
}

std::time_t NeuralNetwork::getCreationDate()
{
	return std::time(nullptr);
}

NeuralNetworkState NeuralNetwork::getState()
{
	return state;
}

void NeuralNetwork::setState(NeuralNetworkState newState)
{
	state = newState;
}
