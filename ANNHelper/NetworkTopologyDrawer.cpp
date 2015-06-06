#include "NetworkTopologyDrawer.hpp"
#include "AbstractNeuron.hpp"
#include "StandardNeuron.hpp"
#include "AbstractNetworkTopology.hpp"
#include "Edge.hpp"
#include <exception>

NetworkTopologyDrawerOptions::NetworkTopologyDrawerOptions()
{
	height = 300;
	width = 300;
	networkTopology = NULL;	
}


NetworkTopologyDrawer::NetworkTopologyDrawer(int posX_, int posY_, NetworkTopologyDrawerOptions& options_)
	: GraphicObject(posX_, posY_)
{
	options.reset(new NetworkTopologyDrawerOptions(options_));
}

void NetworkTopologyDrawer::refresh()
{
	// Check if all given options are correct
	// Check if the given topology is valud
	if (options->networkTopology == NULL)
		throw std::invalid_argument("The given networkTopology is not valid!");

	// Calculate the offset between two layers (The +2 is needed for input neurons and a border)
	int layerOffset = options->width / (options->networkTopology->getNeurons()->size() + 2);	
	// Go through all layers in the given networkTopology
	int layerIndex = 0;
	for (std::vector<std::vector<StandardNeuron*>>::iterator layer = options->networkTopology->getNeurons()->begin(); layer != options->networkTopology->getNeurons()->end(); layer++, layerIndex++)
	{
		// Calculate the offset between two neurons (The +1 is needed for a border)
		int neuronOffset = options->height / (layer->size() + 1);
		// Go through all neurons in this layer
		int neuronIndex = 0;
		for (std::vector<StandardNeuron*>::iterator neuron = layer->begin(); neuron != layer->end(); neuron++, neuronIndex++)
		{
			// Create a new circle shape
			sf::CircleShape newCircle;		

			// Set the position (The +1 is needed for a border)
			newCircle.setPosition((layerIndex + 1) * layerOffset, (neuronIndex + 1) * neuronOffset);	

			// Set the style of the circle shape
			newCircle.setFillColor(sf::Color::Transparent);
			newCircle.setOutlineColor(sf::Color::White);
			newCircle.setOutlineThickness(1);
			newCircle.setRadius(20);
			newCircle.setOrigin(newCircle.getRadius() , newCircle.getRadius());
			newCircle.setPointCount(100);		

			// Add the shape to the map
			neuronShapes[*neuron] = newCircle;
		}
	}

	// Go through the whole neuronShape map
	for (std::map<AbstractNeuron*, sf::CircleShape>::iterator neuronShape = neuronShapes.begin(); neuronShape != neuronShapes.end(); neuronShape++)
	{
		// Go through all efferent edges of the current neuron
		for (std::list<Edge*>::iterator edge = neuronShape->first->getEfferentEdges()->begin(); edge != neuronShape->first->getEfferentEdges()->end(); edge++)
		{
			// Create a new VertexArray (Line)
			sf::VertexArray newVertexArray(sf::PrimitiveType::Lines, 2);
			// Set the start to the position of the prevNeuron shape
			newVertexArray[0].position = neuronShapes[(*edge)->getPrevNeuron()].getPosition();
			// Set the start to the position of the nextNeuron shape
			newVertexArray[1].position = neuronShapes[(*edge)->getNextNeuron()].getPosition();
			// Add a small vertical offset to make recurrent edges visible
			newVertexArray[0].position.y -= 5;
			newVertexArray[1].position.y += 5;
			// Add it to the list
			edgeShapes.push_back(newVertexArray);
		}
	}
}

void NetworkTopologyDrawer::draw(sf::RenderWindow &window)
{	
	// Go through the whole neuronShape map
	for (std::map<AbstractNeuron*, sf::CircleShape>::iterator neuronShape = neuronShapes.begin(); neuronShape != neuronShapes.end(); neuronShape++)
	{
		// Draw the neuron shape
		window.draw(neuronShape->second);
	}
	// Go through the whole edgeShape list
	for (std::list<sf::VertexArray>::iterator edgeShape = edgeShapes.begin(); edgeShape != edgeShapes.end(); edgeShape++)
	{
		// Draw the edge shape
		window.draw(*edgeShape);
	}
}

