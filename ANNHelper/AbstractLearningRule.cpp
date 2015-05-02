#include "AbstractLearningRule.hpp"
#include <vector>
#include "AbstractNeuron.hpp"
#include "NeuralNetwork.hpp"
#include "LayeredNetwork.hpp"
#include "Teacher.hpp"
#include "StandardNeuron.hpp"
#include "AbstractTeachingLesson.hpp"
#include "AbstractActivationOrder.hpp"

#include <iomanip>
#include <iostream>

AbstractLearningRule::AbstractLearningRule(AbstractLearningRuleOptions& options_)
{
	options.reset(&options_);

	// Check if all given options are correct
	if (options->totalErrorGoal < 0)
		throw std::invalid_argument("The totalErrorGoal has to be greater than or equal to 0");
	if (options->maxTotalErrorValue <= options->totalErrorGoal)
		throw std::invalid_argument("The maxTotalErrorValue has to be greater than the totalErrorGoal");
}

bool AbstractLearningRule::doLearning(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	// Check if all given options are correct
	if (teacher.getTeachingLessons()->size() == 0)
		throw std::invalid_argument("The given teacher does not contain any teachingLessons. So what should i learn??");

	// Let the learning algorithm do stuff before starting
	initializeLearningAlgoritm(neuralNetwork, teacher);

	// Ask for the used activation order
	std::unique_ptr<AbstractActivationOrder> activationOrder(getNewActivationOrder());

	// Get all output neurons
	std::vector<AbstractNeuron*>* outputNeurons = neuralNetwork.getNetworkTopology()->getOutputNeurons();
	// Create a vector which will contain all weights for offline learning
	std::vector<float> offlineLearningWeights(dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getEdgeCount());

	int tryCounter = 0;
	float totalError = 0;
	
	// Start a new try
	do
	{
		// Randomize all weights
		neuralNetwork.getNetworkTopology()->randomizeWeights(options->minRandomWeightValue, options->maxRandomWeightValue);
		
		// If debug is enabled, print every n-th iteration a short debug info
		if (options->enableDebugOutput)
			std::cout << "--------------" << std::endl << "Start Try: " << tryCounter << std::endl;

		int iteration = 0;
		// Do while the totalError is not zero
		while ((totalError = teacher.getTotalError(neuralNetwork, *activationOrder)) > options->totalErrorGoal && iteration++ < options->maxIterationsPerTry )
		{			
			// If its not the first iteration and the learning process has stopped, skip that try
			if (iteration > 1 && learningHasStopped())
			{	
				// If debug is enabled, print a short debug info
				if (options->enableDebugOutput)
					std::cout << "Skip that try (learning has stopped)" << std::endl;		
				break;
			}

			// If we had more iterations than minIterationsPerTry and the totalError is still greater than the maxTotalErrorValue, skip that try
			if (iteration > options->minIterationsPerTry && totalError > options->maxTotalErrorValue)
			{
				// If debug is enabled, print a short debug info
				if (options->enableDebugOutput)
					std::cout << "Skip that try (totalError: " << std::fixed << std::setprecision(8) << totalError << " > " << std::fixed << std::setprecision(8) << options->maxTotalErrorValue << ")" << std::endl;
				break;
			}

			// If debug is enabled, print every n-th iteration a short debug info
			if (options->enableDebugOutput && iteration % options->debugOutputInterval == 0)
			{
				std::cout << "TotalError: " << std::fixed << std::setprecision(8) << totalError << " Iteration: " << iteration << " " ;
				printDebugOutput();
				std::cout << std::endl;
			}

			// If offlineLearning is activated, reset the offlineLearningGradients
			if (options->offlineLearning)
			{
				for (std::vector<float>::iterator offlineLearningWeight = offlineLearningWeights.begin(); offlineLearningWeight != offlineLearningWeights.end(); offlineLearningWeight++)
					*offlineLearningWeight = 0;
			}

			// Go through every TeachingLesson
			int lessonIndex = 0;
			for (std::vector<std::unique_ptr<AbstractTeachingLesson>>::iterator teachingLesson = teacher.getTeachingLessons()->begin(); teachingLesson != teacher.getTeachingLessons()->end(); teachingLesson++, lessonIndex++)
			{
				// Calculate the errorvector 
				std::unique_ptr<std::vector<float>> errorvector = (*teachingLesson)->getErrorvector(neuralNetwork, *activationOrder);
				
				// Create a edgeCounter, which will be used in offline learning
				int edgeCounter = 0;

				// Adjust all layers except the first one
				for (int l = dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getLayerCount() - 1; l > 0; l--)
				{			
					// Go through all neurons in this layer
					std::vector<AbstractNeuron*>* neuronsInLayer = dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getNeuronsInLayer(l);
					int neuronsInLayerCount = neuronsInLayer->size();
					int neuronIndex = 0;
					for (std::vector<AbstractNeuron*>::iterator neuron = neuronsInLayer->begin(); neuron != neuronsInLayer->end(); neuron++, neuronIndex++)
					{		
						if (l == dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getLayerCount() - 1 || neuronIndex + 1 < neuronsInLayerCount || !dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->usesBiasNeurons()) // If its the last layer or a BiasNeuron
						{
							// Let the algorithm do some work for the actual neuron
							initializeNeuronWeightCalculation(dynamic_cast<StandardNeuron*>(*neuron), lessonIndex, l, neuronIndex, dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getLayerCount(), neuronsInLayerCount, errorvector.get());

							std::vector<Edge*>* afferentEdges = (dynamic_cast<StandardNeuron*>(*neuron))->getAfferentEdges();
							// Go through all afferentEdges of the actual neuron
							int edgeIndex = 0;
							for (std::vector<Edge*>::iterator edge = afferentEdges->begin(); edge != afferentEdges->end(); edge++, edgeIndex++)
							{			
								// Calculate the deltaWeight
								float deltaWeight = calculateDeltaWeightFromEdge(*edge, lessonIndex, l, neuronIndex, edgeIndex, dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getLayerCount(), neuronsInLayerCount, errorvector.get());

								// If offline learning is activated, add the weight to the offlineLearningWeight, else adjust the weight right now
 								if (options->offlineLearning)
									offlineLearningWeights[edgeCounter++] += deltaWeight;
								else
									adjustWeight(*edge, deltaWeight);
							}	
						}
					}
				}
			}

			// If offline learning is activated, adjust all weights
			if (options->offlineLearning)
			{
				// Create a edgeCounter
				int edgeCounter = 0;

				// Adjust the last and the second last layer
				for (int l = dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getLayerCount() - 1; l > 0; l--)
				{
					// Go through all neurons in this layer
					std::vector<AbstractNeuron*>* neuronsInLayer = dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getNeuronsInLayer(l);
					int neuronsInLayerCount = neuronsInLayer->size();
					int neuronIndex = 0;
					for (std::vector<AbstractNeuron*>::iterator neuron = neuronsInLayer->begin(); neuron != neuronsInLayer->end(); neuron++, neuronIndex++)
					{						
						// If its the last layer
						if (l == dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getLayerCount() - 1)
						{							
							std::vector<Edge*>* afferentEdges = (dynamic_cast<StandardNeuron*>(*neuron))->getAfferentEdges();
							// Go through all afferentEdges of the actual neuron
							for (std::vector<Edge*>::iterator edge = afferentEdges->begin(); edge != afferentEdges->end(); edge++)
							{	
								// Adjust the weight depending on the sum of all calculated gradients
								adjustWeight(*edge, offlineLearningWeights[edgeCounter++] / offlineLearningWeights.size());							
							}							
						}
						else if (neuronIndex + 1 < neuronsInLayerCount) // If its the second last layer and not a BiasNeuron
						{
							std::vector<Edge*>* afferentEdges = (dynamic_cast<StandardNeuron*>(*neuron))->getAfferentEdges();
							
							// Go through all afferentEdges of the actual neuron
							for (std::vector<Edge*>::iterator afferentEdge = afferentEdges->begin(); afferentEdge != afferentEdges->end(); afferentEdge++)
							{				
								// Adjust the weight depending on the sum of all calculated gradients
								adjustWeight(*afferentEdge, offlineLearningWeights[edgeCounter++] / offlineLearningWeights.size());
							}
						}	
					}
				}
			}
		}
	} while (totalError > options->totalErrorGoal && tryCounter++ < options->maxTries);
	
	// Print, If goal has reached 
	if (options->enableDebugOutput)
	{
		if (totalError <= options->totalErrorGoal)
			std::cout << "Try (No. " << tryCounter << ") was successful " << "(totalError: " << std::fixed << std::setprecision(8) << totalError << " < " << std::fixed << std::setprecision(8) << options->totalErrorGoal << ")" << std::endl;
		else
			std::cout << "All tries failed => stop learning" << std::endl;
	}
	// Return if learning was successful
	return (totalError <= options->totalErrorGoal);
}