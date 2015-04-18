#include "NeuralNetwork.hpp"
#include "NetworkTopology.hpp"
#include "Neuron.hpp"
#include "ActivationOrder.hpp"
#include "InputNeuron.hpp"

NeuralNetwork::~NeuralNetwork()
{

}

NeuralNetwork::NeuralNetwork(NetworkTopology* networkTopology_)
{
	networkTopology = networkTopology_;
}

void NeuralNetwork::refreshAllNeurons(ActivationOrder &activationOrder)
{
	// Pass the work to the activationOrder :)
	activationOrder.executeActivation(*networkTopology);
}

std::unique_ptr<std::vector<float>> NeuralNetwork::getOutput()
{
	// Get all output Neurons
	std::vector<Neuron*>* outputNeurons = networkTopology->getOutputNeurons();
	
	// Create a new float vector, which will contain all output values
	std::unique_ptr<std::vector<float>> outputValues(new std::vector<float>());

	// Go through all neurons and copy the activation values into the output vector
	for (std::vector<Neuron*>::iterator neuron = outputNeurons->begin(); neuron != outputNeurons->end(); neuron++)
	{
		outputValues->push_back((*neuron)->getActivation());
	}

	return outputValues;
}

void NeuralNetwork::setInput(std::vector<float> &inputVector)
{
	// Get all input Neurons
	std::vector<Neuron*>* inputNeurons = networkTopology->getInputNeurons();

	// Go through all neurons and copy the input values into the inputNeurons
	int index = 0;
	for (std::vector<Neuron*>::iterator neuron = inputNeurons->begin(); neuron != inputNeurons->end() && index < inputVector.size(); neuron++, index++)
	{
		dynamic_cast<InputNeuron*>(*neuron)->setInput(inputVector[index]);
	}
}

NetworkTopology* NeuralNetwork::getNetworkTopology()
{
	return networkTopology;
}