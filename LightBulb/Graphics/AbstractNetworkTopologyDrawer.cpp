// Includes
#include "Graphics\AbstractNetworkTopologyDrawer.hpp"
#include "Neuron\AbstractNeuron.hpp"
#include "Neuron\StandardNeuron.hpp"
#include "NeuralNetwork\NeuralNetwork.hpp"
#include "Neuron\Edge.hpp"
#include "Graphics\Arrow.hpp"
#include "Neuron\BiasNeuron.hpp"
#include "NetworkTopology\AbstractNetworkTopology.hpp"
#include "Function\AbstractActivationFunction.hpp"
// Library includes
#include <iomanip>
#include <exception>
#include <sstream>

const float AbstractNetworkTopologyDrawer::angleDifferenceBetweenContraryEdges = 0.3f;
const sf::Color AbstractNetworkTopologyDrawer::fillColorStandardNeuron = sf::Color::Transparent;
const sf::Color AbstractNetworkTopologyDrawer::fillColorInputNeuron = sf::Color::Color(0, 0, 150);
const sf::Color AbstractNetworkTopologyDrawer::fillColorPositiveActivatedNeuron = sf::Color::Color(0, 255, 0);
const sf::Color AbstractNetworkTopologyDrawer::fillColorNegativeActivatedNeuron = sf::Color::Color(255, 0, 0);
const sf::Color AbstractNetworkTopologyDrawer::outlineColorStandardNeuron = sf::Color::White;
const sf::Color AbstractNetworkTopologyDrawer::outlineColorOutputNeuron = sf::Color::Yellow;

AbstractNetworkTopologyDrawerOptions::AbstractNetworkTopologyDrawerOptions()
{
	posX = 0;
	posY = 0;
	height = 300;
	width = 300;
	network = NULL;	
}


AbstractNetworkTopologyDrawer::AbstractNetworkTopologyDrawer(AbstractNetworkTopologyDrawerOptions& options_)
{
	options.reset(new AbstractNetworkTopologyDrawerOptions(options_));

	currentCalculationInput = NULL;
	
	activationFunction.reset(new HyperbolicTangentFunction());
	threshold.reset(new StandardThreshold(0));
}

void AbstractNetworkTopologyDrawer::addEdgesToAllShapes()
{
	// Go through the whole neuronShape map
	for (auto neuronShape = neuronShapes.begin(); neuronShape != neuronShapes.end(); neuronShape++)
	{	
		// Go through all efferent edges of the current neuron
		for (auto edge = neuronShape->first->getEfferentEdges()->begin(); edge != neuronShape->first->getEfferentEdges()->end(); edge++)
		{
			sf::Vector2f arrowStart, arrowEnd;
			sf::VertexArray additionalLines;

			// If this is not a self referencing edge
			if ((*edge)->getNextNeuron() !=  (*edge)->getPrevNeuron())
			{
				bool aContraryEdgeExists = false;

				// Go through all efferent edges of the current neuron and determin if there is a contrary edge
				for (auto otherEdge = (*edge)->getNextNeuron()->getEfferentEdges()->begin(); otherEdge != (*edge)->getNextNeuron()->getEfferentEdges()->end(); otherEdge++)
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

			// Add the shape to the list
			edgeShapes[*edge].reset(new Arrow(arrowStart, arrowEnd, "", additionalLines));
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
	// Select the fill color depending on if its an output neuron
	if (dynamic_cast<StandardNeuron*>(neuron) && options->network->getNetworkTopology()->isOutputNeuron(static_cast<StandardNeuron*>(neuron)))
		newCircle.setOutlineColor(outlineColorOutputNeuron);
	else
		newCircle.setOutlineColor(outlineColorStandardNeuron);
	newCircle.setOutlineThickness(1);
	newCircle.setRadius(30);
	newCircle.setOrigin(newCircle.getRadius() , newCircle.getRadius());
	newCircle.setPointCount(100);		

	sf::Text newText;
	std::string thresholdString = "";

	// TODO: Also consider networks without bias neurons
	// Search the afferebt edge from the bias neuron
	for (auto edge = options->network->getNetworkTopology()->getBiasNeuron()->getEfferentEdges()->begin(); edge != options->network->getNetworkTopology()->getBiasNeuron()->getEfferentEdges()->end(); edge++)
	{
		if ((*edge)->getNextNeuron() == neuron)
		{
			// The negative weight of this edge is the threshold of this neuron
			thresholdString = floatToString(-(*edge)->getWeight(), 3);
			break;
		}
	}

	// Set the style of the text
	newText.setFont(font);
	newText.setCharacterSize(15);
	newText.setPosition(position.x, position.y);

	// Add the shape to the map
	neuronShapes[neuron] = std::pair<sf::CircleShape, sf::Text>(newCircle, newText);
}

void AbstractNetworkTopologyDrawer::draw(sf::RenderWindow &window)
{	
	// Go through the whole neuronShape map
	for (auto neuronShape = neuronShapes.begin(); neuronShape != neuronShapes.end(); neuronShape++)
	{
		// Draw the neuron shape
		window.draw(neuronShape->second.first);
		// Draw the threshold
		window.draw(neuronShape->second.second);
	}
	// Go through the whole edgeShape list
	for (auto edgeShape = edgeShapes.begin(); edgeShape != edgeShapes.end(); edgeShape++)
	{
		// Draw the edge shape
		edgeShape->second->draw(window);
	}
}

void AbstractNetworkTopologyDrawer::startNewCalculation(NeuralNetworkIO<double>& input, AbstractActivationOrder &activationOrder)
{
	currentCalculationInput = &input;
	currentCalculationActivationOrder = &activationOrder;	
	currentTimeStep = 0;

	options->network->getNetworkTopology()->resetActivation();

	refreshAllActivations();
}

void AbstractNetworkTopologyDrawer::nextCalculationStep()
{
	options->network->calculate(*currentCalculationInput ,*currentCalculationActivationOrder, currentTimeStep, 1);

	refreshAllActivations();
	refreshAllThresholds();

	currentTimeStep++;
}

void AbstractNetworkTopologyDrawer::resetCalculation()
{
	currentCalculationInput = NULL;

	refreshAllActivations();
	refreshAllThresholds();
}


void AbstractNetworkTopologyDrawer::refreshAllWeights()
{
	// Go through the whole edgeShape list
	for (auto edgeShape = edgeShapes.begin(); edgeShape != edgeShapes.end(); edgeShape++)
	{
		// Convert the edge weight to a string with 3 fractional digits
		edgeShape->second->setDescription(floatToString(edgeShape->first->getWeight(), 3));
	}
}

void AbstractNetworkTopologyDrawer::refreshAllThresholds()
{
	// Go through the whole neuronShape map
	for (auto neuronShape = neuronShapes.begin(); neuronShape != neuronShapes.end(); neuronShape++)
	{
		std::string thresholdString;
		double threshold = 0;

		// TODO: Also consider networks without bias neurons
		// Search the afferebt edge from the bias neuron
		for (auto edge = options->network->getNetworkTopology()->getBiasNeuron()->getEfferentEdges()->begin(); edge != options->network->getNetworkTopology()->getBiasNeuron()->getEfferentEdges()->end(); edge++)
		{
			if ((*edge)->getNextNeuron() == neuronShape->first)
			{
				// The negative weight of this edge is the threshold of this neuron
				thresholdString = floatToString(-(*edge)->getWeight(), 3);
				threshold = -(*edge)->getWeight();
				break;
			}
		}

		if (currentCalculationInput)
		{
			std::ostringstream ss;
			if (dynamic_cast<StandardNeuron*>(neuronShape->first))
			{
				thresholdString = floatToString(static_cast<StandardNeuron*>(neuronShape->first)->getNetInput() + threshold, 3) + "/\n" + thresholdString;
			}
			else
			{
				thresholdString = floatToString(neuronShape->first->getActivation(), 3);
			}
		}

		// Set the style of the text
		neuronShape->second.second.setString(thresholdString);
		
		// Calculate the bounds of the text and set its origin to the center
		sf::FloatRect textRect = neuronShape->second.second.getLocalBounds();
		neuronShape->second.second.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
	}
}

void AbstractNetworkTopologyDrawer::refreshAllActivations()
{
	// Go through the whole neuronShape map
	for (auto neuronShape = neuronShapes.begin(); neuronShape != neuronShapes.end(); neuronShape++)
	{
		if (currentCalculationInput)
		{
			double activationFactor = neuronShape->first->getActivation();		

			activationFactor = activationFunction->execute(activationFactor, threshold.get());
			
			if (activationFactor > 0)
				neuronShape->second.first.setFillColor(sf::Color(fillColorPositiveActivatedNeuron.r, fillColorPositiveActivatedNeuron.g, fillColorPositiveActivatedNeuron.b,  255.0 * activationFactor));
			else
				neuronShape->second.first.setFillColor(sf::Color(fillColorNegativeActivatedNeuron.r, fillColorNegativeActivatedNeuron.g, fillColorNegativeActivatedNeuron.b,  255.0 * -activationFactor));

			for (auto edge = neuronShape->first->getEfferentEdges()->begin(); edge != neuronShape->first->getEfferentEdges()->end(); edge++)
			{
				double edgeActivationFactor = (*edge)->getWeight() * neuronShape->first->getActivation();
				edgeActivationFactor = activationFunction->execute(edgeActivationFactor, threshold.get());

				if (edgeActivationFactor > 0)
					edgeShapes[*edge]->setColor(sf::Color((255 - fillColorPositiveActivatedNeuron.r) * (1 - edgeActivationFactor) + fillColorPositiveActivatedNeuron.r,  (255 - fillColorPositiveActivatedNeuron.g) * (1 - edgeActivationFactor) + fillColorPositiveActivatedNeuron.g, (255 - fillColorPositiveActivatedNeuron.b) * (1 - edgeActivationFactor) + fillColorPositiveActivatedNeuron.b));
				else
					edgeShapes[*edge]->setColor(sf::Color((255 - fillColorNegativeActivatedNeuron.r) * (1 + edgeActivationFactor) + fillColorNegativeActivatedNeuron.r,  (255 - fillColorNegativeActivatedNeuron.g) * (1 + edgeActivationFactor) + fillColorNegativeActivatedNeuron.g, (255 - fillColorNegativeActivatedNeuron.b) * (1 + edgeActivationFactor) + fillColorNegativeActivatedNeuron.b));
			}
		}
		else
		{
			// Select the fill color depending on if its an input neuron
			if (options->network->getNetworkTopology()->isInputNeuron(neuronShape->first))
				neuronShape->second.first.setFillColor(fillColorInputNeuron);
			else
				neuronShape->second.first.setFillColor(fillColorStandardNeuron);
			for (auto edge = neuronShape->first->getEfferentEdges()->begin(); edge != neuronShape->first->getEfferentEdges()->end(); edge++)
			{
				edgeShapes[*edge]->setColor(sf::Color::White);
			}
		}
	}
}