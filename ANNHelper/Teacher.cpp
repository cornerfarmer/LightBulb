#include "Teacher.hpp"
#include "ActivationOrder.hpp"
#include "TeachingLesson.hpp"

void Teacher::addTeachingLesson(TeachingLesson* newTeachingLesson)
{
	// Add the newTeachingLesson to the list
	teachingLessons.push_back(newTeachingLesson);
}

std::vector<TeachingLesson*>* Teacher::getTeachingLessons()
{
	return &teachingLessons;
}

float Teacher::getTotalError(NeuralNetwork &neuralNetwork, ActivationOrder &activationOrder)
{
	float totalError = 0;

	// Add every specific error to the total error
	for (std::vector<TeachingLesson*>::iterator teachingLesson = teachingLessons.begin(); teachingLesson != teachingLessons.end(); teachingLesson++)
	{
		totalError += (*teachingLesson)->getSpecificError(neuralNetwork, activationOrder);
	}
	
	return totalError;
}