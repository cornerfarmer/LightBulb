// Includes
#include "Learning/AbstractLearningRule.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
#include "Teaching/Teacher.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
#include "ActivationOrder/AbstractActivationOrder.hpp"
// Library includes
#include <iomanip>
#include <iostream>
#include <vector>
#include <limits>
#include <list>

AbstractLearningRule::AbstractLearningRule(AbstractLearningRuleOptions* options_)
{
	options.reset(options_);

	// Check if all given options are correct

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
	std::unique_ptr<AbstractActivationOrder> activationOrder(getNewActivationOrder(initializedNeuralNetwork));

	// Let the learning algorithm do stuff before starting
	initializeLearningAlgoritm(initializedNeuralNetwork, initializedTeacher, *activationOrder);

	// Create a vector which will contain all weights for offline learning
	std::vector<std::vector<std::vector<double>>> offlineLearningWeights(initializedNeuralNetwork.getNetworkTopology()->getLayerCount());

	// Adjust all hidden/output layers except 
	for (int l = initializedNeuralNetwork.getNetworkTopology()->getLayerCount() - 1; l >= 0; l--)
	{
		offlineLearningWeights[l].resize(initializedNeuralNetwork.getNetworkTopology()->getNeuronCountInLayer(l));
		// Go through all neurons in this layer
		for (unsigned int n = 0; n < initializedNeuralNetwork.getNetworkTopology()->getNeuronCountInLayer(l); n++)
		{
			offlineLearningWeights[l][n].resize(initializedNeuralNetwork.getNetworkTopology()->getAfferentEdgeCount(l, n));
		}
	}
	
	// Reset all counter
	tryCounter = 0;
	totalError = 0;
	
	currentNetworkTopology = initializedNeuralNetwork.getNetworkTopology();
	currentNeuralNetwork = &initializedNeuralNetwork;
	currentTeacher = &initializedTeacher;
	
	// Start a new try
	do
	{
		// Reset the iteration counter
		iteration = 0;

		// Initialize a new try
		initializeTry(initializedNeuralNetwork, initializedTeacher);
		
		// If debug is enabled, print every n-th iteration a short debug info
		if (options->enableDebugOutput)
			std::cout << "--------------" << std::endl << "Start Try: " << tryCounter << std::endl;

		
		// Do while the totalError is not zero
		while ((totalError = initializedTeacher.getTotalError(initializedNeuralNetwork, *activationOrder)) > options->totalErrorGoal  && iteration++ < options->maxIterationsPerTry)
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
				// Adjust all hidden/output layers except 
				for (int l = initializedNeuralNetwork.getNetworkTopology()->getNeurons()->size() - 1; l >= 0; l--)
				{
					// Go through all neurons in this layer
					for (unsigned int n = 0; n < initializedNeuralNetwork.getNetworkTopology()->getNeuronCountInLayer(l); n++)
					{
						// Go through all afferentEdges of the actual neuron
						for (int edgeIndex = 0; edgeIndex < initializedNeuralNetwork.getNetworkTopology()->getAfferentEdgeCount(l, n); edgeIndex++)
						{
							offlineLearningWeights[l][n][edgeIndex] = 0;
						}
					}
				}
			}

			// Do some work before every iteration
			initializeIteration(initializedNeuralNetwork, initializedTeacher, *activationOrder);

			// Go through every TeachingLesson
			int lessonIndex = 0;
			for (auto teachingLesson = initializedTeacher.getTeachingLessons()->begin(); teachingLesson != initializedTeacher.getTeachingLessons()->end(); teachingLesson++, lessonIndex++)
			{
				// Do some work before every teaching lesson
				initializeTeachingLesson(initializedNeuralNetwork, **teachingLesson);

				// Do some work before all weights will be adjusted
				if (!options->offlineLearning)
					initializeAllWeightAdjustments(initializedNeuralNetwork);

				// Set start and time counter to default values
				int nextStartTime = -1;
				int nextTimeStepCount = -1;

				// While the learning rule wants do some calculation with the current teaching lesson
				while(configureNextErroMapCalculation(&nextStartTime, &nextTimeStepCount, **teachingLesson))
				{
					// Calculate the errormap and also fill - if needed - the output and netInput values map
					std::unique_ptr<ErrorMap_t> errormap = (*teachingLesson)->getErrormap(initializedNeuralNetwork, *activationOrder, /*nextStartTime, nextTimeStepCount,*/  getOutputValuesInTime(), getNetInputValuesInTime());
				
					// Adjust all hidden/output layers except 
					for (int l = initializedNeuralNetwork.getNetworkTopology()->getLayerCount() - 1; l >= 0; l--)
					{			
						// Let the algorithm do some work for the actual neuron
						initializeLayerCalculation(*teachingLesson->get(), lessonIndex, l, errormap.get());

						// Calculate the deltaWeight
						Eigen::MatrixXf deltaWeight = calculateDeltaWeightFromLayer(*teachingLesson->get(), lessonIndex, l, errormap.get());

						// If offline learning is activated, add the weight to the offlineLearningWeight, else adjust the weight right now
						if (options->offlineLearning)
							offlineLearningWeights[l][n][edgeIndex] += deltaWeight;
						else
							offlineLearningWeights[l][n][edgeIndex] = deltaWeight;
					}

					// If offline learning is activated, adjust all weights
					if (!options->offlineLearning)
					{
						// Adjust the every hidden/output layer
						for (int l = initializedNeuralNetwork.getNetworkTopology()->getLayerCount() - 1; l >= 0; l--)
						{
							// Go through all neurons in this layer
							for (unsigned int n = 0; n < initializedNeuralNetwork.getNetworkTopology()->getNeuronCountInLayer(l); n++)
							{
								// Go through all afferentEdges of the actual neuron
								for (int edgeIndex = 0; edgeIndex < initializedNeuralNetwork.getNetworkTopology()->getAfferentEdgeCount(l, n); edgeIndex++)
								{
									// Adjust the weight depending on the sum of all calculated gradients
									adjustWeight(l, n, edgeIndex, offlineLearningWeights[l][n][edgeIndex]);
								}					
							}
						}
					}		

				}
				
				// Do some work after all weights were adjusted
				if (!options->offlineLearning)
					doCalculationAfterAllWeightAdjustments(initializedNeuralNetwork);
			}

			// If offline learning is activated, adjust all weights
			if (options->offlineLearning)
			{
				// Do some work before all weights will be adjusted
				initializeAllWeightAdjustments(initializedNeuralNetwork);

				// Adjust the every hidden/output layer
				for (int l = initializedNeuralNetwork.getNetworkTopology()->getLayerCount() - 1; l >= 0; l--)
				{
					// Go through all neurons in this layer
					for (unsigned int n = 0; n < initializedNeuralNetwork.getNetworkTopology()->getNeuronCountInLayer(l); n++)
					{
						// Go through all afferentEdges of the actual neuron
						for (int edgeIndex = 0; edgeIndex < initializedNeuralNetwork.getNetworkTopology()->getAfferentEdgeCount(l, n); edgeIndex++)
						{
							// Adjust the weight depending on the sum of all calculated gradients
							adjustWeight(l, n, edgeIndex, offlineLearningWeights[l][n][edgeIndex] / offlineLearningWeights.size());							
						}					
					}
				}

				// Do some work after all weights were adjusted
				doCalculationAfterAllWeightAdjustments(initializedNeuralNetwork);
			}
		}
	} while ((totalError > options->totalErrorGoal || abs(totalError) == std::numeric_limits<double>::infinity()) && ++tryCounter < options->maxTries);
	
	// Print, If goal has reached 
	if (options->enableDebugOutput)
	{
		if (totalError <= options->totalErrorGoal)
			std::cout << "Try (No. " << tryCounter << ", " << iteration << " iterations needed) was successful " << "(totalError: " << std::fixed << std::setprecision(8) << totalError << " < " << std::fixed << std::setprecision(8) << options->totalErrorGoal << ")" << std::endl;
		else
			std::cout << "All tries failed => stop learning" << std::endl;
	}
	
	doCalculationAfterLearningProcess(initializedNeuralNetwork, initializedTeacher);

	// Return if learning was successful
	return (totalError <= options->totalErrorGoal);
}

bool AbstractLearningRule::configureNextErroMapCalculation(int* nextStartTime, int* nextTimeStepCount, AbstractTeachingLesson& teachingLesson)
{
	// Per default only calculate every teaching lesson once in all possible timesteps
	if (*nextStartTime != -1)
		return false;
	else
	{
		*nextStartTime = 0;
		*nextTimeStepCount = -1;
		return true;
	}
}
