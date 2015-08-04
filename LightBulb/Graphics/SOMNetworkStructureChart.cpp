// Includes
#include "Graphics\SOMNetworkStructureChart.hpp"
#include "NetworkTopology\SOMNetwork.hpp"
#include "Neuron\StandardNeuron.hpp"
#include "NetworkTopology\AbstractSOMStructure.hpp"
// Library include
#include <list>

SOMNetworkStructureChart::SOMNetworkStructureChart(SOMNetworkStructureChartOptions &options_)
	: AbstractNetworkStructureChart(new SOMNetworkStructureChartOptions(options_))
{
	// Check if all given options are correct
	// Check if the given neural network is valid
	if (getOptions()->somNetwork == NULL)
		throw std::invalid_argument("The given somNetwork is not valid");
	// Check if the indices are correct
	if (options->xNeuronCoordinateIndex >= getNeurons()->size())
		throw std::invalid_argument("Can't find any coordinate with index 'xNeuronCoordinateIndex'");
	if (options->yNeuronCoordinateIndex >= getNeurons()->size())
		throw std::invalid_argument("Can't find any coordinate with index 'yNeuronCoordinateIndex'");
}

std::vector<StandardNeuron*>* SOMNetworkStructureChart::getNeurons()
{
	return &getOptions()->somNetwork->getNeurons()->front();
}

double SOMNetworkStructureChart::getRadiusOfNeuron(StandardNeuron& neuron)
{
	return 0.04;
}

std::vector<double> SOMNetworkStructureChart::getPositionOfNeuron(StandardNeuron& neuron)
{
	return neuron.getAfferentWeightsVector();
}

SOMNetworkStructureChartOptions* SOMNetworkStructureChart::getOptions()
{
	return static_cast<SOMNetworkStructureChartOptions*>(options);
}

void SOMNetworkStructureChart::recalculateAllValues()
{
	AbstractNetworkStructureChart::recalculateAllValues();

	std::map<StandardNeuron*, std::list<StandardNeuron*>>* neighborhoodNeurons = getOptions()->somNetwork->getStructure()->getNeighborhoodNeurons();
	// Create a new VertexArray
	lines = sf::VertexArray(sf::Lines);
	
	std::map<StandardNeuron*, bool> visitedNeurons;
	// Go through all neuron shapes
	for (auto neuronShape = neuronShapes.begin(); neuronShape != neuronShapes.end(); neuronShape++)
	{		
		visitedNeurons[neuronShape->first] = true;
		for (auto connectedNeuron = (*neighborhoodNeurons)[neuronShape->first].begin(); connectedNeuron != (*neighborhoodNeurons)[neuronShape->first].end(); connectedNeuron++)
		{
			if (!visitedNeurons[*connectedNeuron])
			{
				lines.append(sf::Vertex(neuronShape->second.getPosition()));
				lines.append(sf::Vertex(neuronShapes[*connectedNeuron].getPosition()));
			}
		}
	}
	
}

void SOMNetworkStructureChart::draw(sf::RenderWindow &window)
{
	AbstractNetworkStructureChart::draw(window);

	window.draw(lines);
}