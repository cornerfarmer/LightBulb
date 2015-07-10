#include "Graphics\AbstractNetworkTopologyDrawer.hpp"
#include "Neuron\AbstractNeuron.hpp"
#include "Neuron\StandardNeuron.hpp"
#include "NetworkTopology\AbstractNetworkTopology.hpp"
#include "Neuron\Edge.hpp"
#include "Graphics\Arrow.hpp"
#include "Neuron\BiasNeuron.hpp"
#include <iomanip>
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
	for (std::map<AbstractNeuron*, std::pair<sf::CircleShape, sf::Text>>::iterator neuronShape = neuronShapes.begin(); neuronShape != neuronShapes.end(); neuronShape++)
	{	
		// Go through all efferent edges of the current neuron
		for (std::list<Edge*>::iterator edge = neuronShape->first->getEfferentEdges()->begin(); edge != neuronShape->first->getEfferentEdges()->end(); edge++)
		{
			sf::Vector2f arrowStart, arrowEnd;
			sf::VertexArray additionalLines;

			// If this is not a self referencing edge
			if ((*edge)->getNextNeuron() !=  (*edge)->getPrevNeuron())
			{
				bool aContraryEdgeExists = false;

				// Go through all efferent edges of the current neuron and determin if there is a contrary edge
				for (std::list<Edge*>::iterator otherEdge = (*edge)->getNextNeuron()->getEfferentEdges()->begin(); otherEdge != (*edge)->getNextNeuron()->getEfferentEdges()->end(); otherEdge++)
				{
					aContraryEdgeExists |=  ((*otherEdge)->getNextNeuron() == neuronShape->first);
				}

				// Calculate the angle of the line beetween the two neurons of this edge
                float angle = calcAngleFromLine(neuronShapes[(*edge)->getPrevNeuron()].first.getPosition(), neuronShapes[(*edge)->getNextNeuron()].first.getPosition());
			      
				// Calculate the start and end point of the arrow on the neuronShape border. Also consider if there is a contrary edge.
				arrowStart = calcCartesianFromPolarCoordinates(neuronShapes[(*edge)->getPrevNeuron()].first.getPosition(), 30, angle - (aContraryEdgeExists ? angleDifferenceBetweenContraryEdges : 0));
				arrowEnd = calcCartesianFromPolarCoordinates(neuronShapes[(*edge)->getNextNeuron()].first.getPosition(), 30, angle + (float)M_PI + (aContraryEdgeExists ? angleDifferenceBetweenContraryEdges : 0));
      		}
			else
			{
				// Calculate the first two points of the self referencing edge
				arrowEnd = calcCartesianFromPolarCoordinates(neuronShapes[(*edge)->getPrevNeuron()].first.getPosition(), 30, 5.5);
				arrowStart = calcCartesianFromPolarCoordinates(arrowEnd, 30, 5.5);

				// Calculate all linepositions of the referencing edge
				additionalLines.resize(4);
				additionalLines[0] = arrowStart;
				additionalLines[1] = calcCartesianFromPolarCoordinates(arrowStart, 30, 5.25f - (float)M_PI / 2);
				additionalLines[2] = additionalLines[1];
				additionalLines[3] = calcCartesianFromPolarCoordinates(additionalLines[2].position, 30, 5.25f - (float)M_PI);
			}

			// Convert the edge weight to a string with 3 fractional digits
			std::ostringstream ss;
			ss << std::fixed << std::setprecision(3) << (*edge)->getWeight();
			std::string weightString(ss.str());

			// Add the shape to the list
			edgeShapes.push_back(Arrow(arrowStart, arrowEnd, weightString, additionalLines));
		}
	}
}


void AbstractNetworkTopologyDrawer::addShapeFromNeuron(AbstractNeuron* neuron, sf::Vector2f position)
{
	// Create a new circle shape
	sf::CircleShape newCircle;		

	// Set the position to the shape
	newCircle.setPosition(position.x, position.y);	

	// Set the style of the circle shape
	newCircle.setFillColor(sf::Color::Transparent);
	newCircle.setOutlineColor(sf::Color::White);
	newCircle.setOutlineThickness(1);
	newCircle.setRadius(30);
	newCircle.setOrigin(newCircle.getRadius() , newCircle.getRadius());
	newCircle.setPointCount(100);		

	sf::Text newText;
	std::string thresholdString = "";

	// TODO: Also consider networks without bias neurons
	// Search the afferebt edge from the bias neuron
	for (std::list<Edge*>::iterator edge = options->networkTopology->getBiasNeuron()->getEfferentEdges()->begin(); edge != options->networkTopology->getBiasNeuron()->getEfferentEdges()->end(); edge++)
	{
		if ((*edge)->getNextNeuron() == neuron)
		{
			// The negative weight of this edge is the threshold of this neuron
			std::ostringstream ss;
			ss << std::fixed << std::setprecision(3) << -(*edge)->getWeight();
			thresholdString = ss.str();
			break;
		}
	}

	// Set the style of the text
	newText.setString(thresholdString);
	newText.setFont(font);
	newText.setCharacterSize(15);
	newText.setPosition(position.x, position.y);

	// Calculate the bounds of the text and set its origin to the center
	sf::FloatRect textRect = newText.getLocalBounds();
	newText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);

	// Add the shape to the map
	neuronShapes[neuron] = std::pair<sf::CircleShape, sf::Text>(newCircle, newText);
}

void AbstractNetworkTopologyDrawer::draw(sf::RenderWindow &window)
{	
	// Go through the whole neuronShape map
	for (std::map<AbstractNeuron*, std::pair<sf::CircleShape, sf::Text>>::iterator neuronShape = neuronShapes.begin(); neuronShape != neuronShapes.end(); neuronShape++)
	{
		// Draw the neuron shape
		window.draw(neuronShape->second.first);
		// Draw the threshold
		window.draw(neuronShape->second.second);
	}
	// Go through the whole edgeShape list
	for (std::list<Arrow>::iterator edgeShape = edgeShapes.begin(); edgeShape != edgeShapes.end(); edgeShape++)
	{
		// Draw the edge shape
		edgeShape->draw(window);
	}
}

