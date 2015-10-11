// Includes
#include "Graphics/FreeNetworkTopologyDrawer.hpp"
#include "Neuron/AbstractNeuron.hpp"
#include "Neuron/StandardNeuron.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "Neuron/Edge.hpp"
#include "NetworkTopology/FreeNetwork.hpp"
// Library includes
#include <exception>


FreeNetworkTopologyDrawer::FreeNetworkTopologyDrawer(AbstractNetworkTopologyDrawerOptions& options_)
	: AbstractNetworkTopologyDrawer(options_)
{

}

void FreeNetworkTopologyDrawer::refresh()
{
	// Check if all given options are correct
	// Check if the given topology is valid
	if (options->network == NULL)
		throw std::invalid_argument("The given network is not valid!");
	// Check if the given topology is a FreeNetwork
	if (!dynamic_cast<FreeNetwork*>(options->network->getNetworkTopology()))
		throw std::invalid_argument("The networkTopology of the given network has to be a FreeNetwork!");

	bool drawExtraInputNeurons = static_cast<FreeNetwork*>(options->network->getNetworkTopology())->options->realInputNeurons;

	// Place all neurons on the border of a circle
    float angleDistance = ((float)M_PI * 2) / options->network->getNetworkTopology()->getNeurons()->front().size();
	sf::Vector2f center(options->posX + options->width / 2.0f, options->posY + options->height / 2.0f);
	sf::Vector2f radiusVector((options->width - drawExtraInputNeurons * 100) / 2 * 0.9f, options->height / 2 * 0.9f);
	int neuronIndex = 0;
	for (auto neuron = options->network->getNetworkTopology()->getNeurons()->front().begin(); neuron != options->network->getNetworkTopology()->getNeurons()->front().end(); neuron++, neuronIndex++)
	{
		addShapeFromNeuron(*neuron, calcCartesianFromPolarCoordinates(center, radiusVector, neuronIndex * angleDistance + M_PI / 4) + sf::Vector2f(drawExtraInputNeurons * 100, 0));        
	}

	if (drawExtraInputNeurons)
	{
		int neuronIndex = 1;
		for (auto neuron = options->network->getNetworkTopology()->getInputNeurons()->begin(); neuron != options->network->getNetworkTopology()->getInputNeurons()->end(); neuron++, neuronIndex++)
		{
			addShapeFromNeuron(*neuron, sf::Vector2f(50, neuronIndex * options->height / (options->network->getNetworkTopology()->getInputNeurons()->size() + 1)));        
		}
	}

	// Recalculate all data
	addEdgesToAllShapes();
	refreshAllThresholds();
	refreshAllWeights();
	refreshAllActivations();
}

