#include "FreeNetworkTopologyDrawer.hpp"
#include "AbstractNeuron.hpp"
#include "StandardNeuron.hpp"
#include "AbstractNetworkTopology.hpp"
#include "Edge.hpp"
#include <exception>


FreeNetworkTopologyDrawer::FreeNetworkTopologyDrawer(AbstractNetworkTopologyDrawerOptions& options_)
	: AbstractNetworkTopologyDrawer(options_)
{

}

void FreeNetworkTopologyDrawer::refresh()
{
	// Check if all given options are correct
	// Check if the given topology is valud
	if (options->networkTopology == NULL)
		throw std::invalid_argument("The given networkTopology is not valid!");

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
