// Includes
#include "ActivationOrder/SynchronousOrder.hpp"
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "Neuron/StandardNeuron.hpp"
// Library includes
#include <exception>

namespace LightBulb
{
	void SynchronousOrder::executeActivation(AbstractNetworkTopology &networkTopology)
	{
		// Go through all layers
		for (auto layer = networkTopology.getNeurons()->begin(); layer != networkTopology.getNeurons()->end(); layer++)
		{
			// First recalculate the netInput of all neurons in the current layer
			for (auto neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
				(*neuron)->refreshNetInput();

		}
		// Go through all layers
		for (auto layer = networkTopology.getNeurons()->begin(); layer != networkTopology.getNeurons()->end(); layer++)
		{
			// Then recalculate the activation of all neurons in the current layer
			for (auto neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
				(*neuron)->refreshActivation();
		}
	}

	AbstractActivationOrder* SynchronousOrder::getCopy()
	{
		return new SynchronousOrder(*this);
	}

	std::unique_ptr<std::map<Edge*, bool>> SynchronousOrder::getSameTimestepEdges(AbstractNetworkTopology &networkTopology)
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
}