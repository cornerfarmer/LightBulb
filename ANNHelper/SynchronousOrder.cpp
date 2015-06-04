#include "SynchronousOrder.hpp"
#include "LayeredNetwork.hpp"
#include "AbstractNeuron.hpp"
#include <exception>

void SynchronousOrder::executeActivation(AbstractNetworkTopology &networkTopology)
{
	// Go through all layers
	for (std::vector<std::vector<AbstractNeuron*>>::iterator layer = networkTopology.getNeurons()->begin(); layer != networkTopology.getNeurons()->end(); layer++)
	{
		// First recalculate the netInput of all neurons in the current layer
		for (std::vector<AbstractNeuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)		
			(*neuron)->refreshNetInput();
	
	}
	// Go through all layers
	for (std::vector<std::vector<AbstractNeuron*>>::iterator layer = networkTopology.getNeurons()->begin(); layer != networkTopology.getNeurons()->end(); layer++)
	{
		// Then recalculate the activation of all neurons in the current layer
		for (std::vector<AbstractNeuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)		
			(*neuron)->refreshActivation();
	}
}

AbstractActivationOrder* SynchronousOrder::getCopy()
{
	return new SynchronousOrder(*this);
}

std::unique_ptr<std::map<Edge*, bool>> SynchronousOrder::getSameTimestepEdges(AbstractNetworkTopology &networkTopology)
{
	// Cast the network as an layeredNetwork
	LayeredNetwork* layeredNetwork = dynamic_cast<LayeredNetwork*>(&networkTopology);

	// Check if the given networkTopology was a layeredNetwork, else throw a exception
	if (!layeredNetwork)
		throw std::invalid_argument("The given networkTopology has to be a layeredNetwork");

	// Only recurrent edges are not in the same time step
	return layeredNetwork->getNonRecurrentEdges();
}