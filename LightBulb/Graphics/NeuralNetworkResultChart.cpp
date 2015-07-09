#include "Graphics\NeuralNetworkResultChart.hpp"
#include "NeuralNetwork\NeuralNetwork.hpp"
#include "NetworkTopology\AbstractNetworkTopology.hpp"
#include "ActivationOrder\TopologicalOrder.hpp"
#include "NeuralNetwork\NeuralNetworkIO.hpp"
#include <exception>

NeuralNetworkResultChartOptions::NeuralNetworkResultChartOptions()
{
	posX = 0;
	posY = 0;
	binaryInterpretation = true;
	height = 300;
	width = 300;
	neuralNetwork = NULL;
	xInputNeuronIndex = 0;
	xRangeStart = 0;
	xRangeEnd = 1;
	yInputNeuronIndex = 1;
	yRangeStart = 0;
	yRangeEnd = 1;
	activationOrder = NULL;
	outputNeuronIndex = 0;
	ouputRangeStart = 0;
	ouputRangeEnd = 1;
	ouputTimeStep = 0;
	xTimeStep = 0;
	yTimeStep = 0;
}

NeuralNetworkResultChartOptions::~NeuralNetworkResultChartOptions()
{
	delete(activationOrder);
}

NeuralNetworkResultChartOptions::NeuralNetworkResultChartOptions(const NeuralNetworkResultChartOptions &obj)
{
	*this = obj;
	activationOrder = obj.activationOrder->getCopy();
}


NeuralNetworkResultChart::NeuralNetworkResultChart(NeuralNetworkResultChartOptions& options_)
{
	options.reset(new NeuralNetworkResultChartOptions(options_));

	// Check if all given options are correct
	// Check if the given neural network is valid
	if (options->neuralNetwork == NULL)
		throw std::invalid_argument("The given neuralNetwork is not valid");
	// Check if the given activationOrder is valid
	if (options->activationOrder == NULL)
		throw std::invalid_argument("The given activationOrder is not valid");
	// Check if the output and input neuron indices are correct
	if (options->xInputNeuronIndex >= options->neuralNetwork->getNetworkTopology()->getInputNeurons()->size())
		throw std::invalid_argument("Can't find any inputNeuron with index 'xInputNeuronIndex'");
	if (options->yInputNeuronIndex >= options->neuralNetwork->getNetworkTopology()->getInputNeurons()->size())
		throw std::invalid_argument("Can't find any inputNeuron with index 'yInputNeuronIndex'");
	if (options->outputNeuronIndex >= options->neuralNetwork->getNetworkTopology()->getOutputNeurons()->size())
		throw std::invalid_argument("Can't find any outputNeuron with index 'outputNeuronIndex'");
}

void NeuralNetworkResultChart::recalculateAllValues()
{
	// Create a new pixel array, which will contain all color informations
	std::unique_ptr<sf::Uint8[]> pixels(new sf::Uint8[options->width*options->height*4]);
	// Create a new inputVector with the size of the inputCount
	NeuralNetworkIO<float> input;
	input[options->xTimeStep] = std::vector<float>(options->neuralNetwork->getNetworkTopology()->getInputNeurons()->size(), 0);
	input[options->yTimeStep] = std::vector<float>(options->neuralNetwork->getNetworkTopology()->getInputNeurons()->size(), 0);

	// Go through every pixel
	for(int x = 0; x < options->width; x++)
	{
		for(int y = 0; y < options->height; y++)
		{	
			// Compute the input values from the coordinates and the given range
			input[options->xTimeStep][options->xInputNeuronIndex] = (float)x / options->width * (options->xRangeEnd - options->xRangeStart) + options->xRangeStart;
			input[options->yTimeStep][options->yInputNeuronIndex] = (float)y / options->height * (options->yRangeEnd - options->yRangeStart) + options->yRangeStart;

			// Extract the output
			float output = (*options->neuralNetwork->calculate(input, *options->activationOrder, 0, options->ouputTimeStep + 1))[options->ouputTimeStep][options->outputNeuronIndex];

			// If binaryInterpretation is selected, just use black or white, else interpret the output linear
			if (options->binaryInterpretation)
				output = output > (options->ouputRangeEnd - options->ouputRangeStart) / 2 + options->ouputRangeStart ? 255 : 0;
			else
				output = (output - options->ouputRangeStart) / (options->ouputRangeEnd - options->ouputRangeStart) * 255;

			// Normalize the output
			output = std::max(0.0f, std::min(255.0f, output));

			// Set the calculated color value to the actual pixel 
			pixels[(y * options->width + x) * 4]     = output; // R
			pixels[(y * options->width + x) * 4 + 1] = output; // G
			pixels[(y * options->width + x) * 4 + 2] = output; // B
			pixels[(y * options->width + x) * 4 + 3] = output; // A
		}
	}

	// Create a new Texture
	texture.create(options->width, options->height); 
	// Insert the pixelarray into the texture
	texture.update(pixels.get());
}

void NeuralNetworkResultChart::draw(sf::RenderWindow &window)
{	
	// Create a new sprite from our texture, so we can draw it
	sf::Sprite sprite(texture); 
	// Draw the sprite
	window.draw(sprite);
}

