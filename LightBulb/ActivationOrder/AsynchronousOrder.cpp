// Includes
#include "ActivationOrder/AsynchronousOrder.hpp"
#include "Neuron/StandardNeuron.hpp"
#include "Neuron/InputNeuron.hpp"
#include "Neuron/BiasNeuron.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
// Library includes
#include <exception>

void AsynchronousOrder::executeActivation(AbstractNetworkTopology &networkTopology)
{
	// Go through all layers
	for (auto layer = networkTopology.getNeurons()->begin(); layer != networkTopology.getNeurons()->end(); layer++)
	{		
		for (auto neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)		
		{
			// First recalculate the netInput of all neurons in the current layer
			(*neuron)->refreshNetInput();
			// Then recalculate the activation of all neurons in the current layer
			(*neuron)->refreshActivation();
		}	
	}	
}

AbstractActivationOrder* AsynchronousOrder::getCopy()
{
	return new AsynchronousOrder(*this);
}

std::unique_ptr<std::map<Edge*, bool>> AsynchronousOrder::getSameTimestepEdges(AbstractNetworkTopology &networkTopology)
{
	std::unique_ptr<std::map<Edge*, bool>> sameTimestepEdges(new std::map<Edge*, bool>());

	// Go through all input neurons 
	for (auto neuron = networkTopology.getInputNeurons()->begin(); neuron != networkTopology.getInputNeurons()->end(); neuron++)
	{
		// Only if this is a real inputNeuron
		InputNeuron* inputNeuron = dynamic_cast<InputNeuron*>(*neuron);
		if (inputNeuron)
		{
			// Go through all edges
			for (auto edge = inputNeuron->getEfferentEdges()->begin(); edge != inputNeuron->getEfferentEdges()->end(); edge++)
			{
				// Set the sameTimestep value of this edge to true
				(*sameTimestepEdges)[*edge] = true;
			}
		}
	}	

	// If this network has a bias neuron
	if (networkTopology.getBiasNeuron())
	{
		// Go through all efferent edges of the bias neuron
		for (auto edge = networkTopology.getBiasNeuron()->getEfferentEdges()->begin(); edge != networkTopology.getBiasNeuron()->getEfferentEdges()->end(); edge++)
		{
			// Set the sameTimestep value of this edge to true
			(*sameTimestepEdges)[*edge] = true;
		}
	}

	// Return the calculated map
	return sameTimestepEdges;
}