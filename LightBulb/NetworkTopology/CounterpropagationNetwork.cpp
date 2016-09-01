// Includes
#include "NetworkTopology/CounterpropagationNetwork.hpp"
#include "NeuronFactory/DifferentFunctionsNeuronFactory.hpp"
#include "Function/EuclideanDistance.hpp"
#include "Function/IdentityFunction.hpp"
#include "Neuron/NeuronCompareThreshold.hpp"
#include "Function/MinimumNetInputActivationFunction.hpp"
#include "Neuron/StandardNeuron.hpp"
#include "Function/WeightedSumFunction.hpp"
#include "Function/BinaryFunction.hpp"
#include "Neuron/StandardThreshold.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
#include "Neuron/Edge.hpp"
#include "Teaching/Teacher.hpp"
//  Library includes
#include <algorithm>  

CounterpropagationNetwork::CounterpropagationNetwork(unsigned int inputNeuronCount, unsigned int codebookVectorCount, unsigned int outputNeuronCount)
{
	// Check if all given options are correct
	if (inputNeuronCount == 0)
		throw std::invalid_argument("The given inputNeuronCount has to be greater than 0");
	if (codebookVectorCount == 0)
		throw std::invalid_argument("The given codebookVectorCount has to be greater than 0");
	if (outputNeuronCount == 0)
		throw std::invalid_argument("The given outputNeuronCount has to be greater than 0");

	// Create a new options object
	options.reset(new FeedForwardNetworkTopologyOptions());
	// Set all options
	// Define thresholds and functions
	options->neuronFactory = new DifferentFunctionsNeuronFactory(new NeuronCompareThreshold(NULL), new EuclideanDistance(), new MinimumNetInputActivationFunction(), new IdentityFunction(),
																	new StandardThreshold(0), new WeightedSumFunction(), new IdentityFunction(), new IdentityFunction());
	// Set the neuronCounts in all three layers
	options->neuronsPerLayerCount = std::vector<unsigned int>(3);
	options->neuronsPerLayerCount[0] = inputNeuronCount;
	options->neuronsPerLayerCount[1] = codebookVectorCount;
	options->neuronsPerLayerCount[2] = outputNeuronCount;

	// Build the network
	buildNetwork();

	// Go through all neurons in the hidden layer
	for (auto neuron = neurons.front().begin(); neuron != neurons.front().end(); neuron++)
	{
		// Set the neurons vector of the threshold to the neuron vector of the output layer
		static_cast<NeuronCompareThreshold*>((*neuron)->getThreshold())->setNeurons(&neurons.front());
	}
}

void CounterpropagationNetwork::placeCodebookVectorsOnTeachingLessons(Teacher &teacher)
{
	std::map<StandardNeuron*, bool> readyNeurons;
	std::vector<int> lessonOrder(teacher.getTeachingLessons()->size());
	for (int i = 0; i < teacher.getTeachingLessons()->size(); i++)
	{
		lessonOrder[i] = i;
	}
	std::random_shuffle(lessonOrder.begin(), lessonOrder.end());

	for (auto teachingLessonIndex = lessonOrder.begin(); teachingLessonIndex != lessonOrder.end(); teachingLessonIndex++)
	{
		AbstractTeachingLesson* teachingLesson = (*teacher.getTeachingLessons())[*teachingLessonIndex].get();
		for (auto neuron = neurons.front().begin(); neuron != neurons.front().end(); neuron++)
		{
			if (!readyNeurons[*neuron])
			{
				auto teachingPatternValue = (*teachingLesson->getTeachingPattern())[0].second.begin();
				for (auto edge = (*neuron)->getAfferentEdges()->begin(); edge != (*neuron)->getAfferentEdges()->end(); edge++, teachingPatternValue++)
				{
					(*edge)->setWeight(teachingPatternValue->second + ((double)rand() / RAND_MAX - 0.5) / 1000);
				}
				readyNeurons[*neuron] = true;
				break;
			}
		}
	}
}