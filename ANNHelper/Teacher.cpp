#include "Teacher.hpp"
#include "AbstractActivationOrder.hpp"
#include "AbstractTeachingLesson.hpp"
#include "NeuralNetwork.hpp"
#include "AbstractNetworkTopology.hpp"
#include "AbstractNeuron.hpp"
#include "Edge.hpp"

void Teacher::addTeachingLesson(AbstractTeachingLesson* newTeachingLesson)
{
	// Add the newTeachingLesson to the list
	teachingLessons.push_back(std::unique_ptr<AbstractTeachingLesson>(newTeachingLesson));
}

std::vector<std::unique_ptr<AbstractTeachingLesson>>* Teacher::getTeachingLessons()
{
	return &teachingLessons;
}

float Teacher::getTotalError(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder)
{
	float totalError = 0;

	// Add every specific error to the total error
	for (std::vector<std::unique_ptr<AbstractTeachingLesson>>::iterator teachingLesson = teachingLessons.begin(); teachingLesson != teachingLessons.end(); teachingLesson++)
	{
		totalError += (*teachingLesson)->getSpecificError(neuralNetwork, activationOrder);
	}

	return totalError;
}