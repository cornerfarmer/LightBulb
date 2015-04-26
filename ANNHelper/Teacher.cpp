#include "Teacher.hpp"
#include "AbstractActivationOrder.hpp"
#include "TeachingLesson.hpp"
#include "NeuralNetwork.hpp"
#include "AbstractNetworkTopology.hpp"
#include "AbstractNeuron.hpp"
#include "Edge.hpp"

Teacher::~Teacher()
{
	for (int i = 0; i < teachingLessons.size(); i++)
	{
		delete (teachingLessons[i]);
	}
}

void Teacher::addTeachingLesson(TeachingLesson* newTeachingLesson)
{
	// Add the newTeachingLesson to the list
	teachingLessons.push_back(newTeachingLesson);
}

std::vector<TeachingLesson*>* Teacher::getTeachingLessons()
{
	return &teachingLessons;
}

float Teacher::getTotalError(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder, float weightDecayfac)
{
	float totalError = 0;

	// Add every specific error to the total error
	for (std::vector<TeachingLesson*>::iterator teachingLesson = teachingLessons.begin(); teachingLesson != teachingLessons.end(); teachingLesson++)
	{
		totalError += (*teachingLesson)->getSpecificError(neuralNetwork, activationOrder);
	}

	if (weightDecayfac != 0)
	{
		// Calculate the sum of all weights
		float weightSum = 0;
		for (std::vector<std::vector<AbstractNeuron*>>::const_iterator layer = neuralNetwork.getNetworkTopology()->getNeurons()->begin(); layer != neuralNetwork.getNetworkTopology()->getNeurons()->end(); layer++)
		{
			for (std::vector<AbstractNeuron*>::const_iterator neuron = (*layer).begin(); neuron != (*layer).end(); neuron++)
			{
				for (std::vector<Edge*>::const_iterator edge = (*neuron)->getEfferentEdges()->begin(); edge != (*neuron)->getEfferentEdges()->end(); edge++)
				{
					weightSum += pow((*edge)->getWeight(), 2);
				}
			}
		}

		// Add the weight decay term: weightDecayfac * 0.5 * Σ weight^2
		//totalError += weightDecayfac * 0.5f * weightSum;
	}
	return totalError;
}