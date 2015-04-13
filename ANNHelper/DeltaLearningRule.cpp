#include "DeltaLearningRule.hpp"
#include "Teacher.hpp"
#include "TopologicalOrder.hpp"
#include "TeachingLesson.hpp"
#include "NeuralNetwork.hpp"
#include "Neuron.hpp"
#include "NetworkTopology.hpp"
#include "StandardNeuron.hpp"
#include "Edge.hpp"

bool DeltaLearningRule::doLearning(NeuralNetwork &neuralNetwork, Teacher &teacher)
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

			// Go through all error values and adjust the concerning neurons
			std::list<Neuron*>::iterator outputNeuron = outputNeurons->begin();
			for (std::vector<float>::iterator errorValue = errorvector->begin(); errorValue != errorvector->end(); errorValue++, outputNeuron++)
			{
				// If errorValue is not zero, we have to adjust something
				if (*errorValue != 0)
				{
					std::list<Edge*>* afferentEdges = (dynamic_cast<StandardNeuron*>(*outputNeuron))->getAfferentEdges();
					// Go through all afferentEdges of the actual neuron
					for (std::list<Edge*>::iterator edge = afferentEdges->begin(); edge != afferentEdges->end(); edge++)
					{					
						// Use the delta rule: deltaWeight = learningRate * Output(prevNeuron) * errorValue
						(*edge)->setWeigt((*edge)->getWeight() + 0.5f * (*edge)->getPrevNeuron()->getActivation() * *errorValue);					
					}
				}
			}
		}
	}

	
	// This algorithm will always succeed
	return true;
}