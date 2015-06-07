#include "AbstractNetworkTopologyDrawer.hpp"
#include "AbstractNeuron.hpp"
#include "StandardNeuron.hpp"
#include "AbstractNetworkTopology.hpp"
#include "Edge.hpp"
#include "Arrow.hpp"
#include <exception>
#include <sstream>

const float AbstractNetworkTopologyDrawer::angleDifferenceBetweenContraryEdges = 0.3f;

AbstractNetworkTopologyDrawerOptions::AbstractNetworkTopologyDrawerOptions()
{
	posX = 0;
	posY = 0;
	height = 300;
	width = 300;
	networkTopology = NULL;	
}


AbstractNetworkTopologyDrawer::AbstractNetworkTopologyDrawer(AbstractNetworkTopologyDrawerOptions& options_)
{
	options.reset(new AbstractNetworkTopologyDrawerOptions(options_));
}

void AbstractNetworkTopologyDrawer::addEdgesToAllShapes()
{
	// Go through the whole neuronShape map
	for (std::map<AbstractNeuron*, sf::CircleShape>::iterator neuronShape = neuronShapes.begin(); neuronShape != neuronShapes.end(); neuronShape++)
	{	
		// Go through all efferent edges of the current neuron
		for (std::list<Edge*>::iterator edge = neuronShape->first->getEfferentEdges()->begin(); edge != neuronShape->first->getEfferentEdges()->end(); edge++)
		{
			bool aContraryEdgeExists = false;

			// Go through all efferent edges of the current neuron
			for (std::list<Edge*>::iterator otherEdge = (*edge)->getNextNeuron()->getEfferentEdges()->begin(); otherEdge != (*edge)->getNextNeuron()->getEfferentEdges()->end(); otherEdge++)
			{
				aContraryEdgeExists |=  ((*otherEdge)->getNextNeuron() == neuronShape->first);
			}

			// Create a new VertexArray (Line)
			sf::VertexArray newVertexArray(sf::PrimitiveType::Lines, 2);

			float angle = calcAngleFromLine(neuronShapes[(*edge)->getPrevNeuron()].getPosition(), neuronShapes[(*edge)->getNextNeuron()].getPosition());
			      
			sf::Vector2f arrowStart = calcCartesianFromPolarCoordinates(neuronShapes[(*edge)->getPrevNeuron()].getPosition(), 20, angle - (aContraryEdgeExists ? angleDifferenceBetweenContraryEdges : 0));
			sf::Vector2f arrowEnd = calcCartesianFromPolarCoordinates(neuronShapes[(*edge)->getNextNeuron()].getPosition(), 20, angle + M_PI + (aContraryEdgeExists ? angleDifferenceBetweenContraryEdges : 0));
      
			std::ostringstream ss;
			ss << (*edge)->getWeight();
			std::string weightString(ss.str());
			// Add it to the list
			edgeShapes.push_back(Arrow(arrowStart, arrowEnd, weightString));
		}
	}
}


void AbstractNetworkTopologyDrawer::addShapeFromNeuron(AbstractNeuron* neuron, int posX, int posY)
{
	// Create a new circle shape
	sf::CircleShape newCircle;		

	// Set the position (The +1 is needed for a border)
	newCircle.setPosition(posX, posY);	

	// Set the style of the circle shape
	newCircle.setFillColor(sf::Color::Transparent);
	newCircle.setOutlineColor(sf::Color::White);
	newCircle.setOutlineThickness(1);
	newCircle.setRadius(20);
	newCircle.setOrigin(newCircle.getRadius() , newCircle.getRadius());
	newCircle.setPointCount(100);		

	// Add the shape to the map
	neuronShapes[neuron] = newCircle;
}

void AbstractNetworkTopologyDrawer::draw(sf::RenderWindow &window)
{	
	// Go through the whole neuronShape map
	for (std::map<AbstractNeuron*, sf::CircleShape>::iterator neuronShape = neuronShapes.begin(); neuronShape != neuronShapes.end(); neuronShape++)
	{
		// Draw the neuron shape
		window.draw(neuronShape->second);
	}
	// Go through the whole edgeShape list
	for (std::list<Arrow>::iterator edgeShape = edgeShapes.begin(); edgeShape != edgeShapes.end(); edgeShape++)
	{
		// Draw the edge shape
		edgeShape->draw(window);
	}
}

