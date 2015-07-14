// Includes
#include "Graphics\LayeredNetworkTopologyDrawer.hpp"
#include "Neuron\AbstractNeuron.hpp"
#include "Neuron\StandardNeuron.hpp"
#include "NetworkTopology\AbstractNetworkTopology.hpp"
#include "Neuron\Edge.hpp"
#include "NetworkTopology\LayeredNetwork.hpp"
#include "NeuralNetwork\NeuralNetwork.hpp"
// Library includes
#include <exception>


LayeredNetworkTopologyDrawer::LayeredNetworkTopologyDrawer( AbstractNetworkTopologyDrawerOptions& options_)
	: AbstractNetworkTopologyDrawer(options_)
{

}

void LayeredNetworkTopologyDrawer::refresh()
{
	// Check if all given options are correct
	// Check if the given topology is valud
	if (options->network == NULL)
		throw std::invalid_argument("The given network is not valid!");
	// Check if the given topology is a LayeredNetwork
	if (!dynamic_cast<LayeredNetwork*>(options->network->getNetworkTopology()))
		throw std::invalid_argument("The networkTopology of the given network has to be a LayeredNetwork!");

	// Calculate the offset between two layers (The +2 is needed for input neurons and a border)
	int layerOffset = options->width / (options->network->getNetworkTopology()->getNeurons()->size() + 2);	
	// Go through all layers in the given networkTopology
	int layerIndex = 0;

	{
		// Calculate the offset between two neurons (The +1 is needed for a border)
		int neuronOffset = options->height / (options->network->getNetworkTopology()->getInputNeurons()->size() + 1);
		// Go through all neurons in this layer
		int neuronIndex = 0;
		for (auto neuron = options->network->getNetworkTopology()->getInputNeurons()->begin(); neuron != options->network->getNetworkTopology()->getInputNeurons()->end(); neuron++, neuronIndex++)
		{
			addShapeFromNeuron(*neuron, sf::Vector2f((float)((layerIndex + 1) * layerOffset), (float)((neuronIndex + 1) * neuronOffset)));
		}
	}

	layerIndex++;

	for (auto layer = options->network->getNetworkTopology()->getNeurons()->begin(); layer != options->network->getNetworkTopology()->getNeurons()->end(); layer++, layerIndex++)
	{
		// Calculate the offset between two neurons (The +1 is needed for a border)
		int neuronOffset = options->height / (layer->size() + 1);
		// Go through all neurons in this layer
		int neuronIndex = 0;
		for (auto neuron = layer->begin(); neuron != layer->end(); neuron++, neuronIndex++)
		{
			addShapeFromNeuron(*neuron,	sf::Vector2f((float)((layerIndex + 1) * layerOffset), (float)((neuronIndex + 1) * neuronOffset)));
		}
	}

	addEdgesToAllShapes();
}

