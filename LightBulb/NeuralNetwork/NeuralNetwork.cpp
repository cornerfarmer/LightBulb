#include "NeuralNetwork\NeuralNetwork.hpp"
#include "NetworkTopology\AbstractNetworkTopology.hpp"
#include "Neuron\AbstractNeuron.hpp"
#include "ActivationOrder\AbstractActivationOrder.hpp"
#include "Neuron\InputNeuron.hpp"
#include "NeuralNetwork\NeuralNetworkIO.hpp"
#include "Neuron\StandardNeuron.hpp"
#include <exception>

NeuralNetwork::NeuralNetwork(AbstractNetworkTopology* networkTopology_)
{
	// Check if all given options are correct
	if (!networkTopology_)
		throw std::invalid_argument("The given networkTopology is not valid");

	networkTopology.reset(networkTopology_);
}

std::unique_ptr<NeuralNetworkIO<double>> NeuralNetwork::calculate(NeuralNetworkIO<double>& input, AbstractActivationOrder &activationOrder, int startTime, int timeStepCount, std::vector<std::map<AbstractNeuron*, double>>* outputValuesInTime, std::vector<std::map<AbstractNeuron*, double>>* netInputValuesInTime)
{
	std::unique_ptr<NeuralNetworkIO<double>> output(new NeuralNetworkIO<double>());

	// If the calculation start at time 0
	if (startTime == 0)
	{
		// Reset all activations
		networkTopology->resetActivation();
	}

	// Do for every time step
	for (int timeStep = startTime; (timeStep <= input.getMaxTimeStep() && timeStepCount == 0) || timeStep - startTime < timeStepCount; timeStep++)
	{
		// Set the input into the neural network
		setInput(input.count(timeStep) != 0 ? &input.at(timeStep) : NULL);

		// Pass the work to the activationOrder
		activationOrder.executeActivation(*networkTopology);

		// Extract the output and save it into the output value
		(*output)[timeStep] = *getOutput();

		// If the output values map is not null, fill it with all current output values 
		if (outputValuesInTime != NULL)
			networkTopology->getAllNeuronOutputs((*outputValuesInTime)[timeStep]);
		// If the netInput values map is not null, fill it with all current netInput values 
		if (netInputValuesInTime != NULL)
			networkTopology->getAllNeuronNetInputs((*netInputValuesInTime)[timeStep]);
	}

	return output;
}

std::unique_ptr<std::vector<double>> NeuralNetwork::getOutput()
{
	// Get all output Neurons
	std::vector<StandardNeuron*>* outputNeurons = networkTopology->getOutputNeurons();
	
	// Create a new double vector, which will contain all output values
	std::unique_ptr<std::vector<double>> outputValues(new std::vector<double>());

	// Go through all neurons and copy the activation values into the output vector
	for (auto neuron = outputNeurons->begin(); neuron != outputNeurons->end(); neuron++)
	{
		outputValues->push_back((*neuron)->getActivation());
	}

	return outputValues;
}

void NeuralNetwork::setInput(std::vector<double>* inputVector)
{
	// Get all input Neurons
	std::vector<AbstractNeuron*>* inputNeurons = networkTopology->getInputNeurons();

	// Go through all neurons and copy the input values into the inputNeurons
	unsigned int index = 0;
	for (auto neuron = inputNeurons->begin(); neuron != inputNeurons->end() && (!inputVector || index < inputVector->size()); neuron++, index++)
	{
		InputNeuron* inputNeuron = dynamic_cast<InputNeuron*>(*neuron);
		// If its a real input neuron set the input as input of the neuron
		if (inputNeuron)
			inputNeuron->setInput(inputVector ? (*inputVector)[index] : 0);
		else
		{
			StandardNeuron* standardNeuron = dynamic_cast<StandardNeuron*>(*neuron);
			// If its a standard neuron, set the input as additional input
			if (standardNeuron)
				standardNeuron->setAdditionalInput(inputVector ? (*inputVector)[index] : 0);
			else
				throw std::logic_error("Something went wrong while setting the input values");
		}
	}
}

AbstractNetworkTopology* NeuralNetwork::getNetworkTopology()
{
	return networkTopology.get();
}