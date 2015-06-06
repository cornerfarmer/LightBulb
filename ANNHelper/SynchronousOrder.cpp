#include "SynchronousOrder.hpp"
#include "LayeredNetwork.hpp"
#include "StandardNeuron.hpp"
#include <exception>

void SynchronousOrder::executeActivation(AbstractNetworkTopology &networkTopology)
{
	// Go through all layers
	for (std::vector<std::vector<StandardNeuron*>>::iterator layer = networkTopology.getNeurons()->begin(); layer != networkTopology.getNeurons()->end(); layer++)
	{
		// First recalculate the netInput of all neurons in the current layer
		for (std::vector<StandardNeuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)		
			(*neuron)->refreshNetInput();
	
	}
	// Go through all layers
	for (std::vector<std::vector<StandardNeuron*>>::iterator layer = networkTopology.getNeurons()->begin(); layer != networkTopology.getNeurons()->end(); layer++)
	{
		// Then recalculate the activation of all neurons in the current layer
		for (std::vector<StandardNeuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)		
			(*neuron)->refreshActivation();
	}
}

AbstractActivationOrder* SynchronousOrder::getCopy()
{
	return new SynchronousOrder(*this);
}

std::unique_ptr<std::map<Edge*, bool>> SynchronousOrder::getSameTimestepEdges(AbstractNetworkTopology &networkTopology)
{
	return std::unique_ptr<std::map<Edge*, bool>>(new std::map<Edge*, bool>());;
}