#include "Teacher.hpp"
#include "AbstractActivationOrder.hpp"
#include "AbstractTeachingLesson.hpp"
#include "NeuralNetwork.hpp"
#include "AbstractNetworkTopology.hpp"
#include "AbstractNeuron.hpp"
#include "Edge.hpp"

void Teacher::addTestingLesson(AbstractTeachingLesson* newTestingLesson)
{
	// Add the newTeachingLesson to the list
	testingLessons.push_back(std::unique_ptr<AbstractTeachingLesson>(newTestingLesson));

}
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

	// Add every specific error of the teachingLessons to the total error
	for (std::vector<std::unique_ptr<AbstractTeachingLesson>>::iterator teachingLesson = teachingLessons.begin(); teachingLesson != teachingLessons.end(); teachingLesson++)
	{
		totalError += (*teachingLesson)->getSpecificError(neuralNetwork, activationOrder);
	}

	// Add every specific error of the testingLessons to the total error
	for (std::vector<std::unique_ptr<AbstractTeachingLesson>>::iterator testinggLesson = testingLessons.begin(); testinggLesson != testingLessons.end(); testinggLesson++)
	{
		totalError += (*testinggLesson)->getSpecificError(neuralNetwork, activationOrder);
	}

	return totalError;
}

std::unique_ptr<Teacher> Teacher::unfold()
{
	std::unique_ptr<Teacher> unfoldedTeacher(new Teacher());
	for (std::vector<std::unique_ptr<AbstractTeachingLesson>>::iterator originalTeachingLesson = teachingLessons.begin(); originalTeachingLesson != teachingLessons.end(); originalTeachingLesson++)
	{
		unfoldedTeacher->addTeachingLesson((*originalTeachingLesson)->unfold());
	}
	return unfoldedTeacher;
}

int Teacher::getMaxTimeStep()
{
	int maxTimeStep = 0;
	for (std::vector<std::unique_ptr<AbstractTeachingLesson>>::iterator teachingLesson = teachingLessons.begin(); teachingLesson != teachingLessons.end(); teachingLesson++)
	{
		maxTimeStep = std::max(maxTimeStep, (*teachingLesson)->getMaxTimeStep());
	}
	return maxTimeStep;
}