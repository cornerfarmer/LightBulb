// Includes
#include "NetworkTopology/HopfieldNetwork.hpp"
#include "NeuronFactory/SameNeuronDescriptionFactory.hpp"
#include "Function/IdentityFunction.hpp"
#include "Function/WeightedSumFunction.hpp"
#include "Function/BinaryFunction.hpp"
#include "Function/FermiFunction.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
#include "Teaching/Teacher.hpp"
#include "Neuron/NeuronDescription.hpp"
//  Library includes
#include <algorithm>  

namespace LightBulb
{
	HopfieldNetwork::HopfieldNetwork(unsigned int neuronCount, bool binaryActivationFunction)
	{
		// Check if all given options are correct
		if (neuronCount == 0)
			throw std::invalid_argument("The given neuronCount has to be greater than 0");

		// Create a new options object
		options.reset(new FreeNetworkOptions());
		// Set all options
		options->inputNeuronsIndices.resize(neuronCount);
		options->outputNeuronsIndices.resize(neuronCount);
		for (int i = 0; i < neuronCount; i++)
		{
			options->inputNeuronsIndices[i] = i;
			options->outputNeuronsIndices[i] = i;
		}
		options->useBiasNeuron = false;
		options->selfReferencingEdges = false;
		options->neuronCount = neuronCount;
		// Define thresholds and functions
		throw std::exception("currently not working");
		//options->neuronFactory = new SameNeuronDescriptionFactory(new NetworkDescription(new WeightedSumFunction(), (binaryActivationFunction ? static_cast<AbstractActivationFunction*>(new BinaryFunction(-1)) : static_cast<AbstractActivationFunction*>(new FermiFunction(0.1)))));

		// Build the network
		buildNetwork();

	}
}