#include "DeltaLearningRule.hpp"
#include "Teacher.hpp"
#include "TopologicalOrder.hpp"
#include "TeachingLesson.hpp"
#include "NeuralNetwork.hpp"
#include "Neuron.hpp"
#include "NetworkTopology.hpp"
#include "StandardNeuron.hpp"
#include "Edge.hpp"
#include "LayeredNetwork.hpp"

bool DeltaLearningRule::doLearning(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	// Check if all given parameters are correct
	if (!dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology()))
		throw std::exception();
	if (dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getLayerCount() != 2)
		throw std::exception();
	if (teacher.getTeachingLessons()->size() == 0)
		throw std::exception();

	// The TopologicalOrder will be our activationOrder
	TopologicalOrder activationOrder;

	// Get all output neurons
	std::vector<Neuron*>* outputNeurons = neuralNetwork.getNetworkTopology()->getOutputNeurons();

	// Do while the totalError is not zero
	while (teacher.getTotalError(neuralNetwork, activationOrder, 0) > 0)
	{
		// Go through every TeachingLesson
		for (std::vector<TeachingLesson*>::iterator teachingLesson = teacher.getTeachingLessons()->begin(); teachingLesson != teacher.getTeachingLessons()->end(); teachingLesson++)
		{
			// Calculate the errorvector 
			std::unique_ptr<std::vector<float>> errorvector = (*teachingLesson)->getErrorvector(neuralNetwork, activationOrder);

			// Go through all error values and adjust the concerning neurons
			std::vector<Neuron*>::iterator outputNeuron = outputNeurons->begin();
			for (std::vector<float>::iterator errorValue = errorvector->begin(); errorValue != errorvector->end(); errorValue++, outputNeuron++)
			{
				// If errorValue is not zero, we have to adjust something
				if (*errorValue != 0)
				{
					std::vector<Edge*>* afferentEdges = (dynamic_cast<StandardNeuron*>(*outputNeuron))->getAfferentEdges();
					// Go through all afferentEdges of the actual neuron
					for (std::vector<Edge*>::iterator edge = afferentEdges->begin(); edge != afferentEdges->end(); edge++)
					{					
						// Use the delta rule: deltaWeight = learningRate * Output(prevNeuron) * errorValue
						(*edge)->setWeight((*edge)->getWeight() + 0.5f * (*edge)->getPrevNeuron()->getActivation() * *errorValue);					
					}
				}
			}
		}
	}

	
	// This algorithm will always succeed
	return true;
}