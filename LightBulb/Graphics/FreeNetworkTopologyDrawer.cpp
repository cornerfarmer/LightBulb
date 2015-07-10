// Includes
#include "Graphics\FreeNetworkTopologyDrawer.hpp"
#include "Neuron\AbstractNeuron.hpp"
#include "Neuron\StandardNeuron.hpp"
#include "NetworkTopology\AbstractNetworkTopology.hpp"
#include "Neuron\Edge.hpp"
#include "NetworkTopology\FreeNetwork.hpp"
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
	if (options->networkTopology == NULL)
		throw std::invalid_argument("The given networkTopology is not valid!");
	// Check if the given topology is a FreeNetwork
	if (!dynamic_cast<FreeNetwork*>(options->networkTopology))
		throw std::invalid_argument("The given networkTopology has to be a FreeNetwork!");

	// Place all neurons on the border of a circle
    float angleDistance = ((float)M_PI * 2) / options->networkTopology->getNeurons()->front().size();
	sf::Vector2f center(options->posX + options->width / 2.0f, options->posY + options->height / 2.0f);
	sf::Vector2f radiusVector(options->width / 2 * 0.9f, options->height / 2 * 0.9f);
	int neuronIndex = 0;
	for (auto neuron = options->networkTopology->getNeurons()->front().begin(); neuron != options->networkTopology->getNeurons()->front().end(); neuron++, neuronIndex++)
	{
        addShapeFromNeuron(*neuron, calcCartesianFromPolarCoordinates(center, radiusVector, neuronIndex * angleDistance));        
	}

	addEdgesToAllShapes();
}

