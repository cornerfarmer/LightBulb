// Includes
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "Neuron/AbstractNeuron.hpp"
#include "ActivationOrder/AbstractActivationOrder.hpp"
#include "Neuron/InputNeuron.hpp"
#include "NeuralNetwork/NeuralNetworkIO.hpp"
#include "Neuron/StandardNeuron.hpp"
// Library includes
#include <exception>

NeuralNetwork::NeuralNetwork(AbstractNetworkTopology* networkTopology_)
{
	// Check if all given options are correct
	if (!networkTopology_)
		throw std::invalid_argument("The given networkTopology is not valid");

	networkTopology.reset(networkTopology_);
}

void NeuralNetwork::calculate(NeuralNetworkIO<double>& input, NeuralNetworkIO<double>& output, AbstractActivationOrder &activationOrder, int startTime, int timeStepCount, std::vector<std::map<AbstractNeuron*, double>>* outputValuesInTime, std::vector<std::map<AbstractNeuron*, double>>* netInputValuesInTime, bool resetActivations)
{
	// If the calculation start at time 0
	if (startTime == 0 && resetActivations)
	{
		// Reset all activations
		networkTopology->resetActivation();
	}

	// Do for every time step
	for (int timeStep = startTime; (timeStep <= input.getMaxTimeStep() && timeStepCount == -1) || timeStep - startTime < timeStepCount; timeStep++)
	{
		// Set the input into the neural network
		networkTopology->setInput(input.existsTimestep(timeStep) ? &input[timeStep].second : NULL);

		// Pass the work to the activationOrder
		activationOrder.executeActivation(*networkTopology);

		// Extract the output and save it into the output value
		output.set(timeStep, 0, 0);
		networkTopology->getOutput(output[timeStep].second);

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
	networkTopology->setInput(&input);

	// Pass the work to the activationOrder
	activationOrder.executeActivation(*networkTopology);

	// Extract the output and save it into the output value
	networkTopology->getOutput(output);

}


std::unique_ptr<NeuralNetworkIO<double>> NeuralNetwork::calculate(NeuralNetworkIO<double>& input, AbstractActivationOrder &activationOrder, int startTime, int timeStepCount, std::vector<std::map<AbstractNeuron*, double>>* outputValuesInTime, std::vector<std::map<AbstractNeuron*, double>>* netInputValuesInTime, bool resetActivations)
{
	std::unique_ptr<NeuralNetworkIO<double>> output(new NeuralNetworkIO<double>(networkTopology->getOutputSize()));

	calculate(input, *output.get(), activationOrder, startTime, timeStepCount, outputValuesInTime, netInputValuesInTime, resetActivations);

	return output;
}

AbstractNetworkTopology* NeuralNetwork::getNetworkTopology()
{
	return networkTopology.get();
}
