#include "FreeNetworkTopologyDrawer.hpp"
#include "AbstractNeuron.hpp"
#include "StandardNeuron.hpp"
#include "AbstractNetworkTopology.hpp"
#include "Edge.hpp"
#include "FreeNetwork.hpp"
#include <exception>


FreeNetworkTopologyDrawer::FreeNetworkTopologyDrawer(AbstractNetworkTopologyDrawerOptions& options_)
	: AbstractNetworkTopologyDrawer(options_)
{

}

void FreeNetworkTopologyDrawer::refresh()
{
	// Check if all given options are correct
	// Check if the given topology is valid
	if (options->networkTopology == NULL)
		throw std::invalid_argument("The given networkTopology is not valid!");
	// Check if the given topology is a FreeNetwork
	if (!dynamic_cast<FreeNetwork*>(options->networkTopology))
		throw std::invalid_argument("The given networkTopology has to be a FreeNetwork!");

	// Place all neurons on the border of a circle
	float angleDistance = (M_PI * 2) / options->networkTopology->getNeurons()->front().size();
	sf::Vector2f center(options->posX + options->width / 2, options->posY + options->height / 2);
	sf::Vector2f radiusVector(options->width / 2 * 0.9, options->height / 2 * 0.9);
	int neuronIndex = 0;
	for (std::vector<StandardNeuron*>::iterator neuron = options->networkTopology->getNeurons()->front().begin(); neuron != options->networkTopology->getNeurons()->front().end(); neuron++, neuronIndex++)
	{
		addShapeFromNeuron(*neuron,	calcCartesianFromPolarCoordinates(center, radiusVector, (float)neuronIndex * angleDistance));		
	}

	addEdgesToAllShapes();
}

