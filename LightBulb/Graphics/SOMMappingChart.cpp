// Includes
#include "Graphics\SOMMappingChart.hpp"
#include "NeuralNetwork\NeuralNetwork.hpp"
#include "NetworkTopology\AbstractNetworkTopology.hpp"
#include "ActivationOrder\TopologicalOrder.hpp"
#include "NeuralNetwork\NeuralNetworkIO.hpp"
#include "NetworkTopology\AbstractSOMStructure.hpp"
#include "NetworkTopology\SOMNetwork.hpp"
#include "Neuron\StandardNeuron.hpp"
// Library includes
#include <exception>
#include <vector>

SOMMappingChart::SOMMappingChart(SOMMappingChartOptions& options_)
{
	options.reset(new SOMMappingChartOptions(options_));

	// Check if all given options are correct
	// Check if the given neural network is valid
	if (options->somNetwork == NULL)
		throw std::invalid_argument("The given somNetwork is not valid");
	// Check if the output and input neuron indices are correct
	if (options->rInputNeuronIndex >= options->somNetwork->getInputNeurons()->size())
		throw std::invalid_argument("Can't find any inputNeuron with index 'rInputNeuronIndex'");
	if (options->gInputNeuronIndex >= options->somNetwork->getInputNeurons()->size())
		throw std::invalid_argument("Can't find any inputNeuron with index 'gInputNeuronIndex'");
	if (options->bInputNeuronIndex >= options->somNetwork->getOutputNeurons()->size())
		throw std::invalid_argument("Can't find any inputNeuron with index 'bInputNeuronIndex'");
}

void SOMMappingChart::recalculateAllValues()
{	
	AbstractSOMStructure* structure = options->somNetwork->getStructure();
	// Go through all neurons
	for (auto neuron = options->somNetwork->getNeurons()->front().begin(); neuron != options->somNetwork->getNeurons()->front().end(); neuron++)
	{
		// Set the position from the position of the neurons in the structure
		rectangles[*neuron].setPosition((*structure->getNeuronPositionsInStructure())[*neuron][0] * options->scalingX, (*structure->getNeuronPositionsInStructure())[*neuron].size() > 1 ? (*structure->getNeuronPositionsInStructure())[*neuron][1] * options->scalingY : 0);
		// Sets the size of the rectangle depending of the zoom
		rectangles[*neuron].setSize(sf::Vector2f(options->scalingX, (int)options->scalingY));
		// Calculate the color
		sf::Color color;
		std::vector<double> weightVector = (*neuron)->getAfferentWeightsVector();		
		color.r = (char)((weightVector[options->rInputNeuronIndex] - options->rRangeStart) / (options->rRangeEnd - options->rRangeStart) * 255);
		color.g = (char)((weightVector[options->gInputNeuronIndex] - options->gRangeStart) / (options->gRangeEnd - options->gRangeStart) * 255);
		color.b = (char)((weightVector[options->bInputNeuronIndex] - options->bRangeStart) / (options->bRangeEnd - options->bRangeStart) * 255);
		rectangles[*neuron].setFillColor(color);
	}
}

void SOMMappingChart::draw(sf::RenderWindow &window)
{	
	// Go through all rectangles and draw them
	for (auto rectangle = rectangles.begin(); rectangle != rectangles.end(); rectangle++)
	{
		window.draw(rectangle->second);
	}
}

