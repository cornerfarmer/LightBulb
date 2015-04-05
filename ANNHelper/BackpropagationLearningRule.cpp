#include "BackpropagationLearningRule.hpp"
#include "Teacher.hpp"
#include "TopologicalOrder.hpp"
#include "TeachingLesson.hpp"
#include "NeuralNetwork.hpp"
#include "LayeredNetwork.hpp"
#include "Neuron.hpp"
#include "NetworkTopology.hpp"
#include "StandardNeuron.hpp"
#include "Edge.hpp"

void BackpropagationLearningRule::doLearning(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	// The TopologicalOrder will be our activationOrder
	TopologicalOrder activationOrder;

	// Get all output neurons
	std::list<Neuron*>* outputNeurons = neuralNetwork.getNetworkTopology()->getOutputNeurons();

	// Do while the totalError is not zero
	while (teacher.getTotalError(neuralNetwork, activationOrder) > 0)
	{
		// Go through every TeachingLesson
		for (std::list<TeachingLesson*>::iterator teachingLesson = teacher.getTeachingLessons()->begin(); teachingLesson != teacher.getTeachingLessons()->end(); teachingLesson++)
		{
			// Calculate the errorvector 
			std::unique_ptr<std::vector<float>> errorvector = (*teachingLesson)->getErrorvector(neuralNetwork, activationOrder);

			// Create a vector which will contain all delta values of the neurons in the output layer
			std::vector<float> deltaVectorOutputLayer(errorvector->size(), 0);

			// Adjust the last and the second last layer
			for (int l = 2; l > 0; l--)
			{			
				// Go through all neurons in this layer
				std::list<Neuron*>* neuronsInLayer = dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getNeuronsInLayer(l);
				int neuronsInLayerCount = neuronsInLayer->size();
				int neuronIndex = 0;
				for (std::list<Neuron*>::iterator neuron = neuronsInLayer->begin(); neuron != neuronsInLayer->end(); neuron++, neuronIndex++)
				{
					// If its the last layer
					if (l == 2)
					{
						// If errorValue is not zero, we have to adjust something
						if ((*errorvector)[neuronIndex] != 0)
						{
							std::list<Edge*>* afferentEdges = (dynamic_cast<StandardNeuron*>(*neuron))->getAfferentEdges();
							// Go through all afferentEdges of the actual neuron
							for (std::list<Edge*>::iterator edge = afferentEdges->begin(); edge != afferentEdges->end(); edge++)
							{					
								// Compute the delta value: activationFunction'(netInput) * errorValue
								deltaVectorOutputLayer[neuronIndex] = (dynamic_cast<StandardNeuron*>(*neuron))->executeDerivationOnActivationFunction((dynamic_cast<StandardNeuron*>(*neuron))->getNetInput()) * (*errorvector)[neuronIndex];
								// Change the weight: deltaWeight = learningRate * Output(prevNeuron) * deltaValue
								(*edge)->setWeigt((*edge)->getWeight() + 0.5f * (*edge)->getPrevNeuron()->getActivation() * deltaVectorOutputLayer[neuronIndex]);		
							}
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
							nextLayerErrorValueFactor += deltaVectorOutputLayer[efferentEdgeIndex] * (*efferentEdge)->getWeight();
						}

						// Go through all afferentEdges of the actual neuron
						for (std::list<Edge*>::iterator afferentEdge = afferentEdges->begin(); afferentEdge != afferentEdges->end(); afferentEdge++)
						{
							// Change the weight: deltaWeight = learningRate * Output(prevNeuron) * activationFunction'(netInput) * nextLayerErrorValueFactor
							(*afferentEdge)->setWeigt((*afferentEdge)->getWeight() + 0.5f * (*afferentEdge)->getPrevNeuron()->getActivation() * (dynamic_cast<StandardNeuron*>(*neuron))->executeDerivationOnActivationFunction((dynamic_cast<StandardNeuron*>(*neuron))->getNetInput()) * nextLayerErrorValueFactor);		
						}
					}
				}
			}
		}
	}
}