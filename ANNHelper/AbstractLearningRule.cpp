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

AbstractLearningRule::AbstractLearningRule(AbstractLearningRuleOptions* options_)
{
	options.reset(options_);

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

	Teacher& initializedTeacher = *initializeTeacher(teacher);
	NeuralNetwork& initializedNeuralNetwork = *initializeNeuralNetwork(neuralNetwork);
	
	// Ask for the used activation order
	std::unique_ptr<AbstractActivationOrder> activationOrder(getNewActivationOrder());

	// Let the learning algorithm do stuff before starting
	initializeLearningAlgoritm(initializedNeuralNetwork, initializedTeacher, *activationOrder);

	// Get all output neurons
	std::vector<StandardNeuron*>* outputNeurons = initializedNeuralNetwork.getNetworkTopology()->getOutputNeurons();
	// Create a vector which will contain all weights for offline learning
	std::vector<float> offlineLearningWeights(initializedNeuralNetwork.getNetworkTopology()->getEdgeCount());

	int tryCounter = 0;
	float totalError = 0;
	
	// Start a new try
	do
	{
		// Initialize a new try
		initializeTry(initializedNeuralNetwork, initializedTeacher);
		
		// If debug is enabled, print every n-th iteration a short debug info
		if (options->enableDebugOutput)
			std::cout << "--------------" << std::endl << "Start Try: " << tryCounter << std::endl;

		int iteration = 0;
		// Do while the totalError is not zero
		while ((totalError = initializedTeacher.getTotalError(initializedNeuralNetwork, *activationOrder)) > options->totalErrorGoal && iteration++ < options->maxIterationsPerTry )
		{			
			// If its not the first iteration and the learning process has stopped, skip that try
			if (iteration > 1 && learningHasStopped())
			{	
				// If debug is enabled, print a short debug info
				if (options->enableDebugOutput)
					std::cout << "Skip that try (learning has stopped with totalError: " << std::fixed << std::setprecision(8) << totalError << ")" << std::endl;		
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
			for (std::vector<std::unique_ptr<AbstractTeachingLesson>>::iterator teachingLesson = initializedTeacher.getTeachingLessons()->begin(); teachingLesson != initializedTeacher.getTeachingLessons()->end(); teachingLesson++, lessonIndex++)
			{
				if (!options->offlineLearning)
					initializeAllWeightAdjustments(initializedNeuralNetwork);

				int nextStartTime = -1;
				int nextTimeStepCount = -1;

				while(configureNextErroMapCalculation(&nextStartTime, &nextTimeStepCount, **teachingLesson))
				{
					// Calculate the errormap and also fill - if needed - the output and netInput values map
					std::unique_ptr<ErrorMap_t> errormap = (*teachingLesson)->getErrormap(initializedNeuralNetwork, *activationOrder, nextStartTime, nextTimeStepCount,  getOutputValuesInTime(), getNetInputValuesInTime());
				
					// Create a edgeCounter, which will be used in offline learning
					int edgeCounter = 0;

					// Adjust all hidden/output layers except 
					for (int l = initializedNeuralNetwork.getNetworkTopology()->getNeurons()->size() - 1; l >= 0; l--)
					{			
						// Go through all neurons in this layer
						std::vector<StandardNeuron*>* neuronsInLayer = &(*initializedNeuralNetwork.getNetworkTopology()->getNeurons())[l];
						int neuronsInLayerCount = neuronsInLayer->size();
						for (int n = 0; n < neuronsInLayer->size(); n++)
						{					
							// Let the algorithm do some work for the actual neuron
							initializeNeuronWeightCalculation((*neuronsInLayer)[n], lessonIndex, l, n, initializedNeuralNetwork.getNetworkTopology()->getNeurons()->size(), neuronsInLayerCount, errormap.get());

							std::list<Edge*>* afferentEdges = ((*neuronsInLayer)[n])->getAfferentEdges();
							// Go through all afferentEdges of the actual neuron
							int edgeIndex = 0;
							for (std::list<Edge*>::iterator edge = afferentEdges->begin(); edge != afferentEdges->end(); edge++, edgeIndex++)
							{			
								// Calculate the deltaWeight
								float deltaWeight = calculateDeltaWeightFromEdge(*edge, lessonIndex, l, n, edgeIndex, initializedNeuralNetwork.getNetworkTopology()->getNeurons()->size(), neuronsInLayerCount, errormap.get());

								// If offline learning is activated, add the weight to the offlineLearningWeight, else adjust the weight right now
 								if (options->offlineLearning)
									offlineLearningWeights[edgeCounter++] += deltaWeight;
								else
									offlineLearningWeights[edgeCounter++] = deltaWeight;
							}							
						}
					}

					// If offline learning is activated, adjust all weights
					if (!options->offlineLearning)
					{
						// Create a edgeCounter
						int edgeCounter = 0;

						// Adjust the every hidden/output layer
						for (int l = initializedNeuralNetwork.getNetworkTopology()->getNeurons()->size() - 1; l >= 0; l--)
						{
							// Go through all neurons in this layer
							std::vector<StandardNeuron*>* neuronsInLayer = &(*initializedNeuralNetwork.getNetworkTopology()->getNeurons())[l];
							int neuronsInLayerCount = neuronsInLayer->size();
							for (std::vector<StandardNeuron*>::iterator neuron = neuronsInLayer->begin(); neuron != neuronsInLayer->end(); neuron++)
							{						
								std::list<Edge*>* afferentEdges = (*neuron)->getAfferentEdges();
								// Go through all afferentEdges of the actual neuron
								for (std::list<Edge*>::iterator edge = afferentEdges->begin(); edge != afferentEdges->end(); edge++)
								{	
									// Adjust the weight depending on the sum of all calculated gradients
									adjustWeight(*edge, offlineLearningWeights[edgeCounter++]);							
								}					
							}
						}
					}

			

					if (!options->offlineLearning)
						doCalculationAfterAllWeightAdjustments(initializedNeuralNetwork);
				}
			}

			// If offline learning is activated, adjust all weights
			if (options->offlineLearning)
			{
				initializeAllWeightAdjustments(initializedNeuralNetwork);

				// Create a edgeCounter
				int edgeCounter = 0;

				// Adjust the every hidden/output layer
				for (int l = initializedNeuralNetwork.getNetworkTopology()->getNeurons()->size() - 1; l >= 0; l--)
				{
					// Go through all neurons in this layer
					std::vector<StandardNeuron*>* neuronsInLayer = &(*initializedNeuralNetwork.getNetworkTopology()->getNeurons())[l];
					int neuronsInLayerCount = neuronsInLayer->size();
					for (std::vector<StandardNeuron*>::iterator neuron = neuronsInLayer->begin(); neuron != neuronsInLayer->end(); neuron++)
					{						
						std::list<Edge*>* afferentEdges = (*neuron)->getAfferentEdges();
						// Go through all afferentEdges of the actual neuron
						for (std::list<Edge*>::iterator edge = afferentEdges->begin(); edge != afferentEdges->end(); edge++)
						{	
							// Adjust the weight depending on the sum of all calculated gradients
							adjustWeight(*edge, offlineLearningWeights[edgeCounter++] / offlineLearningWeights.size());							
						}					
					}
				}

				doCalculationAfterAllWeightAdjustments(initializedNeuralNetwork);
			}
		}
	} while ((totalError > options->totalErrorGoal || abs(totalError) == std::numeric_limits<float>::infinity()) && ++tryCounter < options->maxTries);
	
	// Print, If goal has reached 
	if (options->enableDebugOutput)
	{
		if (totalError <= options->totalErrorGoal)
			std::cout << "Try (No. " << tryCounter << ") was successful " << "(totalError: " << std::fixed << std::setprecision(8) << totalError << " < " << std::fixed << std::setprecision(8) << options->totalErrorGoal << ")" << std::endl;
		else
			std::cout << "All tries failed => stop learning" << std::endl;
	}
	
	doCalculationAfterLearningProcess(initializedNeuralNetwork, initializedTeacher);

	// Return if learning was successful
	return (totalError <= options->totalErrorGoal);
}

bool AbstractLearningRule::configureNextErroMapCalculation(int* nextStartTime, int* nextTimeStepCount, AbstractTeachingLesson& teachingLesson)
{
	if (*nextTimeStepCount != -1)
		return false;
	else
	{
		*nextStartTime = 0;
		*nextTimeStepCount = 0;
		return true;
	}
}