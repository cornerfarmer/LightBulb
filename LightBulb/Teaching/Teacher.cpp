// Includes
#include "Teaching/Teacher.hpp"
#include "ActivationOrder/AbstractActivationOrder.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
#include "NeuralNetwork/AbstractNeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"

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

std::vector<std::unique_ptr<AbstractTeachingLesson>>* Teacher::getTestingLessons()
{
	return &testingLessons;
}


double Teacher::getTotalError(AbstractNeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder)
{
	double totalError = 0;

	// Add every specific error of the teachingLessons to the total error
	for (auto teachingLesson = teachingLessons.begin(); teachingLesson != teachingLessons.end(); teachingLesson++)
	{
		totalError += (*teachingLesson)->getSpecificError(neuralNetwork, activationOrder);
	}

	// Add every specific error of the testingLessons to the total error
	for (auto testinggLesson = testingLessons.begin(); testinggLesson != testingLessons.end(); testinggLesson++)
	{
		totalError += (*testinggLesson)->getSpecificError(neuralNetwork, activationOrder);
	}

	return totalError;
}

std::unique_ptr<Teacher> Teacher::unfold()
{
	// Create a new teacher
	std::unique_ptr<Teacher> unfoldedTeacher(new Teacher());
	// Unfold all teaching lessons
	for (auto originalTeachingLesson = teachingLessons.begin(); originalTeachingLesson != teachingLessons.end(); originalTeachingLesson++)
	{
		unfoldedTeacher->addTeachingLesson((*originalTeachingLesson)->unfold());
	}

	// Unfold all testing lessons
	for (auto originalTestingLesson = testingLessons.begin(); originalTestingLesson != testingLessons.end(); originalTestingLesson++)
	{
		unfoldedTeacher->addTestingLesson((*originalTestingLesson)->unfold());
	}
	return unfoldedTeacher;
}

int Teacher::getMaxTimeStep()
{
	int maxTimeStep = 0;
	// Find the biggest timestep of all teaching lessons
	for (auto teachingLesson = teachingLessons.begin(); teachingLesson != teachingLessons.end(); teachingLesson++)
	{
		maxTimeStep = std::max(maxTimeStep, (*teachingLesson)->getMaxTimeStep());
	}
	return maxTimeStep;
}