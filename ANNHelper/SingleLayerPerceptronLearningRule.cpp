#include "SingleLayerPerceptronLearningRule.hpp"
#include "Teacher.hpp"
#include "TopologicalOrder.hpp"
#include "AbstractTeachingLesson.hpp"
#include "NeuralNetwork.hpp"
#include "AbstractNeuron.hpp"
#include "AbstractNetworkTopology.hpp"
#include "StandardNeuron.hpp"
#include "Edge.hpp"
#include "LayeredNetwork.hpp"
#include "BinaryFunction.hpp"

bool SingleLayerPerceptronLearningRule::doLearning(NeuralNetwork &neuralNetwork, Teacher &teacher)
{	
	// Check if all given parameters are correct
	if (!dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology()))
		throw std::invalid_argument("The given neuralNetwork has to contain a layeredNetworkTopology");
	if (dynamic_cast<LayeredNetwork*>(neuralNetwork.getNetworkTopology())->getLayerCount() != 2)
		throw std::invalid_argument("The given neuralNetwork has to contain exactly two layers");
	if (!dynamic_cast<BinaryFunction*>(dynamic_cast<StandardNeuron*>((*neuralNetwork.getNetworkTopology()->getOutputNeurons())[0])->getActivationFunction()))
		throw std::invalid_argument("All outputNeurons have to use binary activationFunctions");
	if (teacher.getTeachingLessons()->size() == 0)
		throw std::invalid_argument("The given teacher does not contain any teachingLessons. So what should i learn??");

	// The TopologicalOrder will be our activationOrder
	TopologicalOrder activationOrder;

	// Get all output neurons
	std::vector<AbstractNeuron*>* outputNeurons = neuralNetwork.getNetworkTopology()->getOutputNeurons();

	// Do while the totalError is not zero
	while (teacher.getTotalError(neuralNetwork, activationOrder, 0) > 0)
	{
		// Go through every TeachingLesson
		for (std::vector<AbstractTeachingLesson*>::iterator teachingLesson = teacher.getTeachingLessons()->begin(); teachingLesson != teacher.getTeachingLessons()->end(); teachingLesson++)
		{
			// Calculate the errorvector 
			std::unique_ptr<std::vector<float>> errorvector = (*teachingLesson)->getErrorvector(neuralNetwork, activationOrder);

			// Go through all error values and adjust the concerning neurons
			std::vector<AbstractNeuron*>::iterator outputNeuron = outputNeurons->begin();
			for (std::vector<float>::iterator errorValue = errorvector->begin(); errorValue != errorvector->end(); errorValue++, outputNeuron++)
			{
				// If errorValue is not zero, we have to adjust something
				if (*errorValue != 0)
				{
					std::vector<Edge*>* afferentEdges = (dynamic_cast<StandardNeuron*>(*outputNeuron))->getAfferentEdges();
					// Go through all afferentEdges of the actual neuron
					for (std::vector<Edge*>::iterator edge = afferentEdges->begin(); edge != afferentEdges->end(); edge++)
					{
						// If the errorValue is positive add the activation to the weight, else substract the activation from the weight
						if (*errorValue > 0)
							(*edge)->setWeight((*edge)->getWeight() + (*edge)->getPrevNeuron()->getActivation());
						else
							(*edge)->setWeight((*edge)->getWeight() - (*edge)->getPrevNeuron()->getActivation());
					}
				}
			}
		}
	}

	// This algorithm will always succeed
	return true;
}