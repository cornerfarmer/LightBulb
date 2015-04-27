#include "NeuralNetwork.hpp"
#include "AbstractNetworkTopology.hpp"
#include "AbstractNeuron.hpp"
#include "AbstractActivationOrder.hpp"
#include "InputNeuron.hpp"
#include <exception>

NeuralNetwork::NeuralNetwork(AbstractNetworkTopology* networkTopology_)
{
	// Check if all given options are correct
	if (!networkTopology_)
		throw std::invalid_argument("The given networkTopology is not valid");

	networkTopology.reset(networkTopology_);
}

void NeuralNetwork::refreshAllNeurons(AbstractActivationOrder &activationOrder)
{
	// Pass the work to the activationOrder :)
	activationOrder.executeActivation(*networkTopology);
}

std::unique_ptr<std::vector<float>> NeuralNetwork::getOutput()
{
	// Get all output Neurons
	std::vector<AbstractNeuron*>* outputNeurons = networkTopology->getOutputNeurons();
	
	// Create a new float vector, which will contain all output values
	std::unique_ptr<std::vector<float>> outputValues(new std::vector<float>());

	// Go through all neurons and copy the activation values into the output vector
	for (std::vector<AbstractNeuron*>::iterator neuron = outputNeurons->begin(); neuron != outputNeurons->end(); neuron++)
	{
		outputValues->push_back((*neuron)->getActivation());
	}

	return outputValues;
}

void NeuralNetwork::setInput(std::vector<float> &inputVector)
{
	// Get all input Neurons
	std::vector<AbstractNeuron*>* inputNeurons = networkTopology->getInputNeurons();

	// Go through all neurons and copy the input values into the inputNeurons
	int index = 0;
	for (std::vector<AbstractNeuron*>::iterator neuron = inputNeurons->begin(); neuron != inputNeurons->end() && index < inputVector.size(); neuron++, index++)
	{
		dynamic_cast<InputNeuron*>(*neuron)->setInput(inputVector[index]);
	}
}

AbstractNetworkTopology* NeuralNetwork::getNetworkTopology()
{
	return networkTopology.get();
}