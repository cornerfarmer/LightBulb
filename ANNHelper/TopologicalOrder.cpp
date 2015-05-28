#include "TopologicalOrder.hpp"
#include "LayeredNetwork.hpp"
#include "AbstractNeuron.hpp"
#include <exception>

void TopologicalOrder::executeActivation(AbstractNetworkTopology &networkTopology)
{

	// Cast the network as an layeredNetwork
	LayeredNetwork* layeredNetwork = dynamic_cast<LayeredNetwork*>(&networkTopology);

	// Check if the given networkTopology was a layeredNetwork, else throw a exception
	if (!layeredNetwork)
		throw std::invalid_argument("The given networkTopology has to be a layeredNetwork");

	// Go through all layers
	for (std::vector<std::vector<AbstractNeuron*>>::iterator layer = layeredNetwork->getNeurons()->begin(); layer != layeredNetwork->getNeurons()->end(); layer++)
	{
		// First recalculate the netInput of all neurons in the current layer
		for (std::vector<AbstractNeuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)		
			(*neuron)->refreshNetInput();
		// Then recalculate the activation of all neurons in the current layer
		for (std::vector<AbstractNeuron*>::iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)		
			(*neuron)->refreshActivation();
	}
}

AbstractActivationOrder* TopologicalOrder::getCopy()
{
	return new TopologicalOrder(*this);
}