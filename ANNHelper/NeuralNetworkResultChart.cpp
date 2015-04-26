#include "NeuralNetworkResultChart.hpp"
#include "NeuralNetwork.hpp"
#include "AbstractNetworkTopology.hpp"
#include "TopologicalOrder.hpp"
#include <exception>

NeuralNetworkResultChart::~NeuralNetworkResultChart()
{
	delete(options);
}

NeuralNetworkResultChart::NeuralNetworkResultChart(int posX_, int posY_, NeuralNetworkResultChartOptions* options_)
	: GraphicObject(posX_, posY_)
{
	options = options_;
}

void NeuralNetworkResultChart::recalculateAllValues()
{
	// Check if all given options are correct
	// Check if the output and input neuron indices are correct
	if (options->xInputNeuronIndex >= options->neuralNetwork->getNetworkTopology()->getInputNeurons()->size())
		throw std::invalid_argument("Can't find any inputNeuron with index 'xInputNeuronIndex'");
	if (options->yInputNeuronIndex >= options->neuralNetwork->getNetworkTopology()->getInputNeurons()->size())
		throw std::invalid_argument("Can't find any inputNeuron with index 'yInputNeuronIndex'");
	if (options->outputNeuronIndex >= options->neuralNetwork->getNetworkTopology()->getOutputNeurons()->size())
		throw std::invalid_argument("Can't find any outputNeuron with index 'outputNeuronIndex'");

	// Create a new pixel array, which will contain all color informations
	sf::Uint8* pixels = new sf::Uint8[options->width*options->height*4];
	// Create a new inputVector with the size of the inputCount
	std::vector<float> inputVector(options->neuralNetwork->getNetworkTopology()->getInputNeurons()->size(), 0);

	// Go through every pixel
	for(int x = 0; x < options->width; x++)
	{
		for(int y = 0; y < options->height; y++)
		{	
			// Compute the input values from the coordinates and the given range
			inputVector[options->xInputNeuronIndex] = (float)x / options->width * (options->xRangeEnd - options->xRangeStart) + options->xRangeStart;
			inputVector[options->yInputNeuronIndex] = (float)y / options->height * (options->yRangeEnd - options->yRangeStart) + options->yRangeStart;
			// Insert the input values
			options->neuralNetwork->setInput(inputVector);
			// Let the NN comput
			options->neuralNetwork->refreshAllNeurons(*options->activationOrder);
			// Extract the output
			float output = (*options->neuralNetwork->getOutput())[options->outputNeuronIndex];

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
	texture.update(pixels);
	// Free the used memory
	delete[](pixels);
}

void NeuralNetworkResultChart::draw(sf::RenderWindow &window)
{	
	// Create a new sprite from our texture, so we can draw it
	sf::Sprite sprite(texture); 
	// Draw the sprite
	window.draw(sprite);
}