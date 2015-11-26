// Includes
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "Neuron/AbstractNeuron.hpp"
#include "Neuron/StandardNeuron.hpp"
#include "Neuron/Edge.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
// Library includes
#include <algorithm>
#include <iostream>

void AbstractNetworkTopology::copyWeightsFrom(AbstractNetworkTopology& otherNetwork)
{
	// Go through all neuron groups of the deeper network
	int gOther = otherNetwork.getNeurons()->size() - 1;
	for (int g = getNeurons()->size() - 1; g >= 0 && gOther >= 0;)
	{
		// Extract the neurons in the current group of both networks
		std::vector<StandardNeuron*>& neuronsInGroup = (*getNeurons())[g];
		std::vector<StandardNeuron*>& neuronsInGroupOther = (*otherNetwork.getNeurons())[gOther];
		// Go through all neurons in the current network
		int neuronIndex = 0;
		std::vector<StandardNeuron*>::iterator neuronOther = neuronsInGroupOther.begin();
		for (auto neuron = neuronsInGroup.begin(); neuron != neuronsInGroup.end() && neuronOther != neuronsInGroupOther.end(); neuron++, neuronOther++, neuronIndex++)
		{
			// Extract all afferent edges of the current neurons
			std::list<Edge*>* afferentEdges = (*neuron)->getAfferentEdges();
			std::list<Edge*>* afferentEdgesOther = (*neuronOther)->getAfferentEdges();
			// Go through all afferentEdges of the actual neurons
			std::list<Edge*>::iterator edgeOther = afferentEdgesOther->begin();
			for (auto edge = afferentEdges->begin(); edge != afferentEdges->end() && edgeOther != afferentEdgesOther->end(); edge++, edgeOther++)
			{	
				// Copy the weight from the edge from the other network into the edge of the own one
				(*edge)->setWeight((*edgeOther)->getWeight());
			}
		}

		// Go one group backwards in the other network
		gOther--;
		// If we reached the input layer and the otherNetwork is not as deep as the own one, then start from the last group in the other network again
		if (gOther == -1 && otherNetwork.getNeurons()->size() < getNeurons()->size())
			gOther = otherNetwork.getNeurons()->size() - 1;

		// Go one group backwards in the own network
		g--;
		// If we reached the input group and the own network is not as deep as the other one, then start from the last group in the own network again
		if (g == -1 && getNeurons()->size() - 1 < otherNetwork.getNeurons()->size())
			g = getNeurons()->size() - 1;
	}
}

double AbstractNetworkTopology::calculateEuclideanDistance(AbstractNetworkTopology& otherNetwork)
{
	double distance = 0;
	// Go synchronously through all edges of the two given objects
	auto neurons1 = getNeurons();
	auto neurons2 = otherNetwork.getNeurons();
	auto layer1 = neurons1->begin();
	for (auto layer2 = neurons2->begin(); layer1 != neurons1->end() && layer2 != neurons2->end(); layer1++, layer2++)
	{
		auto neuron1 = layer1->begin();
		for (auto neuron2 = layer2->begin(); neuron1 != layer1->end() && neuron2 != layer2->end(); neuron1++, neuron2++)
		{
			auto edge1 = (*neuron1)->getAfferentEdges()->begin();
			for (auto edge2 = (*neuron2)->getAfferentEdges()->begin(); edge1 != (*neuron1)->getAfferentEdges()->end() && edge2 != (*neuron2)->getAfferentEdges()->end(); edge1++, edge2++)
			{
				// Calculate the weights average and store it inside the first object
				distance += pow((*edge1)->getWeight() - (*edge2)->getWeight(), 2);
			}
		}
	}
	distance = sqrt(distance);

	//std::cout << (int)distance << std::endl;
	return distance;
}


bool AbstractNetworkTopology::isInputNeuron(AbstractNeuron* neuron)
{
	std::vector<AbstractNeuron*>* inputNeurons = getInputNeurons();
	return std::find(inputNeurons->begin(), inputNeurons->end(), neuron) != inputNeurons->end();
}

bool AbstractNetworkTopology::isOutputNeuron(StandardNeuron* neuron)
{
	std::vector<StandardNeuron*>* outputNeurons = getOutputNeurons();
	return std::find(outputNeurons->begin(), outputNeurons->end(), neuron) != outputNeurons->end();
}


void AbstractNetworkTopology::getOutput(std::vector<std::pair<bool, double>> &outputVector)
{
	// Get all output Neurons
	std::vector<StandardNeuron*>* outputNeurons = getOutputNeurons();

	// Go through all neurons and copy the activation values into the output vector
	int outputNeuronIndex = 0;
	for (auto neuron = outputNeurons->begin(); neuron != outputNeurons->end(); neuron++, outputNeuronIndex++)
	{
		outputVector[outputNeuronIndex].first = true;
		outputVector[outputNeuronIndex].second = (*neuron)->getActivation();
	}
}

void AbstractNetworkTopology::setInput(std::vector<std::pair<bool, double>>* inputVector)
{
	// Get all input Neurons
	std::vector<AbstractNeuron*>* inputNeurons = getInputNeurons();

	// Go through all neurons and copy the input values into the inputNeurons
	unsigned int index = 0;
	for (auto neuron = inputNeurons->begin(); neuron != inputNeurons->end() && (!inputVector || index < inputVector->size()); neuron++, index++)
	{
		InputNeuron* inputNeuron = dynamic_cast<InputNeuron*>(*neuron);
		// If its a real input neuron set the input as input of the neuron
		if (inputNeuron)
			inputNeuron->setInput(inputVector && (*inputVector)[index].first > 0? (*inputVector)[index].second : 0);
		else
		{
			StandardNeuron* standardNeuron = dynamic_cast<StandardNeuron*>(*neuron);
			// If its a standard neuron, set the input as additional input
			if (standardNeuron)
				standardNeuron->setAdditionalInput(inputVector && (*inputVector)[index].first > 0? (*inputVector)[index].second : 0);
			else
				throw std::logic_error("Something went wrong while setting the input values");
		}
	}
}


void AbstractNetworkTopology::getOutput(std::vector<double> &outputVector)
{
	// Get all output Neurons
	std::vector<StandardNeuron*>* outputNeurons = getOutputNeurons();

	// Go through all neurons and copy the activation values into the output vector
	int outputNeuronIndex = 0;
	for (auto neuron = outputNeurons->begin(); neuron != outputNeurons->end(); neuron++, outputNeuronIndex++)
	{
		outputVector[outputNeuronIndex] = (*neuron)->getActivation();
	}
}

void AbstractNetworkTopology::setInput(std::vector<double>* inputVector)
{
	// Get all input Neurons
	std::vector<AbstractNeuron*>* inputNeurons = getInputNeurons();

	// Go through all neurons and copy the input values into the inputNeurons
	unsigned int index = 0;
	for (auto neuron = inputNeurons->begin(); neuron != inputNeurons->end() && (!inputVector || index < inputVector->size()); neuron++, index++)
	{
		InputNeuron* inputNeuron = dynamic_cast<InputNeuron*>(*neuron);
		// If its a real input neuron set the input as input of the neuron
		if (inputNeuron)
			inputNeuron->setInput((*inputVector)[index]);
		else
		{
			StandardNeuron* standardNeuron = dynamic_cast<StandardNeuron*>(*neuron);
			// If its a standard neuron, set the input as additional input
			if (standardNeuron)
				standardNeuron->setAdditionalInput((*inputVector)[index]);
			else
				throw std::logic_error("Something went wrong while setting the input values");
		}
	}
}