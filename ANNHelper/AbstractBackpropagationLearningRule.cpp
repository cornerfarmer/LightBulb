#include "AbstractBackpropagationLearningRule.hpp"
#include "Teacher.hpp"
#include "TopologicalOrder.hpp"
#include "TeachingLesson.hpp"
#include "NeuralNetwork.hpp"
#include "LayeredNetwork.hpp"
#include "Neuron.hpp"
#include "NetworkTopology.hpp"
#include "StandardNeuron.hpp"
#include "Edge.hpp"

AbstractBackpropagationLearningRule::AbstractBackpropagationLearningRule(int maxIterationsPerTry_, int maxTries_, float totalErrorGoal_, float minRandomWeightValue_, float maxRandomWeightValue_)
{
	maxIterationsPerTry = maxIterationsPerTry_;
	maxTries = maxTries_;
	totalErrorGoal = totalErrorGoal_;
	minRandomWeightValue = minRandomWeightValue_;
	maxRandomWeightValue = maxRandomWeightValue_;
}

float AbstractBackpropagationLearningRule::startAlgorithm(NeuralNetwork &neuralNetwork, Teacher &teacher, ActivationOrder &activationOrder, bool offlineLearning)
{	
	// Get all output neurons
	std::list<Neuron*>* outputNeurons = neuralNetwork.getNetworkTopology()->getOutputNeurons();

	std::vector<float> offlineLearningGradients(dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getEdgeCount());

	// Create a vector which will contain all delta values of the neurons in the output layer
	std::vector<std::vector<float>> deltaVectorOutputLayer;
	
	for (std::list<std::list<Neuron*>>::iterator layer = dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getNeurons()->begin(); layer != dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getNeurons()->end(); layer++)
	{
		deltaVectorOutputLayer.push_back(std::vector<float>((*layer).size()));
	}	

	int tryCounter = 0;
	float totalError;
	
	// Start a new try
	do
	{
		// Randomize all weights
		neuralNetwork.getNetworkTopology()->randomizeWeights(minRandomWeightValue, maxRandomWeightValue);
		
		int iteration = 0;
		// Do while the totalError is not zero
		while ((totalError = teacher.getTotalError(neuralNetwork, activationOrder)) > totalErrorGoal && iteration++ < maxIterationsPerTry)
		{
			// If offlineLearning is activated, reset the offlineLearningGradients
			if (offlineLearning)
			{
				for (std::vector<float>::iterator offlineLearningGradient = offlineLearningGradients.begin(); offlineLearningGradient != offlineLearningGradients.end(); offlineLearningGradient++)
					*offlineLearningGradient = 0;
			}

			// Go through every TeachingLesson
			for (std::list<TeachingLesson*>::iterator teachingLesson = teacher.getTeachingLessons()->begin(); teachingLesson != teacher.getTeachingLessons()->end(); teachingLesson++)
			{
				// Calculate the errorvector 
				std::unique_ptr<std::vector<float>> errorvector = (*teachingLesson)->getErrorvector(neuralNetwork, activationOrder);

				

				// Create a edgeCounter, which will be used in offline learning
				int edgeCounter = 0;

				// Adjust the last and the second last layer
				for (int l = dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getLayerCount() - 1; l > 0; l--)
				{			
					// Go through all neurons in this layer
					std::list<Neuron*>* neuronsInLayer = dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getNeuronsInLayer(l);
					int neuronsInLayerCount = neuronsInLayer->size();
					int neuronIndex = 0;
					for (std::list<Neuron*>::iterator neuron = neuronsInLayer->begin(); neuron != neuronsInLayer->end(); neuron++, neuronIndex++)
					{						
						// If its the last layer
						if (l == dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getLayerCount() - 1)
						{						
							
							// Compute the delta value: activationFunction'(netInput) * errorValue
							deltaVectorOutputLayer[l][neuronIndex] = (dynamic_cast<StandardNeuron*>(*neuron))->executeDerivationOnActivationFunction((dynamic_cast<StandardNeuron*>(*neuron))->getNetInput()) * (*errorvector)[neuronIndex];
						
							std::list<Edge*>* afferentEdges = (dynamic_cast<StandardNeuron*>(*neuron))->getAfferentEdges();
							// Go through all afferentEdges of the actual neuron
							for (std::list<Edge*>::iterator edge = afferentEdges->begin(); edge != afferentEdges->end(); edge++)
							{			
								// Calculate the gradient
								// gradient = - Output(prevNeuron) * deltaValue
								float gradient = -1 * (*edge)->getPrevNeuron()->getActivation() * deltaVectorOutputLayer[l][neuronIndex];		

								// If offline learning is activated, add the gradient to the offlineLearningGradient, else adjust the weight right now
								if (offlineLearning)
									offlineLearningGradients[edgeCounter++] += gradient;
								else
									adjustWeight(*edge, gradient);
							}							
						}
						else if (neuronIndex + 1 < neuronsInLayerCount) // If its the second last layer and not a BiasNeuron
						{
							std::list<Edge*>* afferentEdges = (dynamic_cast<StandardNeuron*>(*neuron))->getAfferentEdges();
							std::list<Edge*>* efferentEdges = (*neuron)->getEfferentEdges();

							// Calc the nextLayerErrorValueFactor
							float nextLayerErrorValueFactor = 0;

							// Go through all efferentEdges of the actual neuron and add to the nextLayerErrorValueFactor: deltaValue * edgeWeight
							int efferentEdgeIndex = 0;
							for (std::list<Edge*>::iterator efferentEdge = efferentEdges->begin(); efferentEdge != efferentEdges->end(); efferentEdge++, efferentEdgeIndex++)
							{
								nextLayerErrorValueFactor += deltaVectorOutputLayer[l + 1][efferentEdgeIndex] * (*efferentEdge)->getWeight();
							}

							// Compute the delta value:  activationFunction'(netInput) * nextLayerErrorValueFactor
							deltaVectorOutputLayer[l][neuronIndex] = (dynamic_cast<StandardNeuron*>(*neuron))->executeDerivationOnActivationFunction((dynamic_cast<StandardNeuron*>(*neuron))->getNetInput()) * nextLayerErrorValueFactor;	
						
							// Go through all afferentEdges of the actual neuron
							for (std::list<Edge*>::iterator afferentEdge = afferentEdges->begin(); afferentEdge != afferentEdges->end(); afferentEdge++)
							{
								// Calculate the gradient
								// gradient = - Output(prevNeuron) * deltaValue
								float gradient = -1 * (*afferentEdge)->getPrevNeuron()->getActivation() * deltaVectorOutputLayer[l][neuronIndex];

								// If offline learning is activated, add the gradient to the offlineLearningGradient, else adjust the weight right now
								if (offlineLearning)
									offlineLearningGradients[edgeCounter++] += gradient;
								else
									adjustWeight(*afferentEdge, gradient);
							}
						}	
					}
				}
			}

			// If offline learning is activated, adjust all weights
			if (offlineLearning)
			{
				// Create a edgeCounter
				int edgeCounter = 0;

				// Adjust the last and the second last layer
				for (int l = dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getLayerCount() - 1; l > 0; l--)
				{
					// Go through all neurons in this layer
					std::list<Neuron*>* neuronsInLayer = dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getNeuronsInLayer(l);
					int neuronsInLayerCount = neuronsInLayer->size();
					int neuronIndex = 0;
					for (std::list<Neuron*>::iterator neuron = neuronsInLayer->begin(); neuron != neuronsInLayer->end(); neuron++, neuronIndex++)
					{						
						// If its the last layer
						if (l == dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getLayerCount() - 1)
						{							
							std::list<Edge*>* afferentEdges = (dynamic_cast<StandardNeuron*>(*neuron))->getAfferentEdges();
							// Go through all afferentEdges of the actual neuron
							for (std::list<Edge*>::iterator edge = afferentEdges->begin(); edge != afferentEdges->end(); edge++)
							{	
								// Adjust the weight depending on the sum of all calculated gradients
								adjustWeight(*edge, offlineLearningGradients[edgeCounter++]);
							}							
						}
						else if (neuronIndex + 1 < neuronsInLayerCount) // If its the second last layer and not a BiasNeuron
						{
							std::list<Edge*>* afferentEdges = (dynamic_cast<StandardNeuron*>(*neuron))->getAfferentEdges();
							
							// Go through all afferentEdges of the actual neuron
							for (std::list<Edge*>::iterator afferentEdge = afferentEdges->begin(); afferentEdge != afferentEdges->end(); afferentEdge++)
							{				
								// Adjust the weight depending on the sum of all calculated gradients
								adjustWeight(*afferentEdge, offlineLearningGradients[edgeCounter++]);
							}
						}	
					}
				}
			}
		}
	} while (totalError > totalErrorGoal && tryCounter++ < maxTries);

	return totalError;
}
