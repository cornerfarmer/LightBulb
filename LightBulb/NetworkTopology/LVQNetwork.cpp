// Includes
#include "NetworkTopology/LVQNetwork.hpp"
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

LVQNetwork::LVQNetwork(unsigned int inputNeuronCount, unsigned int codebookVectorCount, unsigned int classCount)
{
	// Check if all given options are correct
	if (inputNeuronCount == 0)
		throw std::invalid_argument("The given inputNeuronCount has to be greater than 0");
	if (codebookVectorCount == 0)
		throw std::invalid_argument("The given codebookVectorCount has to be greater than 0");
	if (classCount == 0)
		throw std::invalid_argument("The given classCount has to be greater than 0");

	// Create a new options object
	options.reset(new FeedForwardNetworkTopologyOptions());
	// Set all options
	// Define thresholds and functions
	options->neuronFactory = new DifferentFunctionsNeuronFactory(new NeuronCompareThreshold(NULL), new EuclideanDistance(), new MinimumNetInputActivationFunction(), new IdentityFunction(),
																	new StandardThreshold(0), new WeightedSumFunction(), new BinaryFunction(), new IdentityFunction());
	// Set the neuronCounts in all three layers
	options->neuronsPerLayerCount = std::vector<unsigned int>(3);
	options->neuronsPerLayerCount[0] = inputNeuronCount;
	options->neuronsPerLayerCount[1] = codebookVectorCount;
	options->neuronsPerLayerCount[2] = classCount;

	// Build the network
	buildNetwork();

	// Go through all neurons in the output layer
	for (auto neuron = neurons.front().begin(); neuron != neurons.front().end(); neuron++)
	{
		// Set the neurons vector of the threshold to the neuron vector of the output layer
		static_cast<NeuronCompareThreshold*>((*neuron)->getThreshold())->setNeurons(&neurons.front());
	}
}

int LVQNetwork::getClassCount()
{	
	return neurons[1].size();
}

int LVQNetwork::getCodebookVectorCount()
{
	return neurons[0].size();
}

int LVQNetwork::getClassOfNeuron(AbstractNeuron* neuron)
{
	auto edgeIndex = 0;

	for (auto edge = neuron->getEfferentEdges()->begin(); edge != neuron->getEfferentEdges()->end(); edge++, edgeIndex++)
	{
		if ((*edge)->getWeight() == 1)
		{
			return edgeIndex;
		}
	}

	throw new std::logic_error("The network has not been configured right");
}

int LVQNetwork::getClassOfNeuronWithIndex(int neuronIndex)
{
	return getClassOfNeuron(neurons[0][neuronIndex]);
}

int LVQNetwork::getClassOfTeachingLesson(AbstractTeachingLesson& teachingLesson)
{
	NeuralNetworkIO<double>* teachingInput = teachingLesson.getTeachingInput(neurons.back()[0]->getActivationFunction());
	for (int teachingInputValueIndex = 0; teachingInputValueIndex < teachingInput->getDimension(); teachingInputValueIndex++)
	{
		if (teachingInput->get(0, teachingInputValueIndex))
			return teachingInputValueIndex;
	}

	throw new std::logic_error("The given teachingLesson is not valid");
}

void LVQNetwork::divideCodebookVectorsIntoClasses()
{
	double codebookVectorsPerClass = (double)getCodebookVectorCount() / getClassCount();

	int neuronIndex = 0;
	for (auto neuron = neurons.back().begin(); neuron != neurons.back().end(); neuron++, neuronIndex++)
	{
		int edgeIndex = 0;
		for (auto edge = (*neuron)->getAfferentEdges()->begin(); edge != (*neuron)->getAfferentEdges()->end(); edge++, edgeIndex++)
		{
			if (edgeIndex >= neuronIndex * codebookVectorsPerClass && edgeIndex < (neuronIndex + 1) * codebookVectorsPerClass)
				(*edge)->setWeight(1);
			else
				(*edge)->setWeight(0);
		}
	}
}
void LVQNetwork::placeCodebookVectorsOnTeachingLessons(Teacher &teacher)
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
			if (!readyNeurons[*neuron] && getClassOfTeachingLesson(*teachingLesson) == getClassOfNeuron(*neuron))
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