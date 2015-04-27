#pragma once

#ifndef _TEACHER_H_
#define _TEACHER_H_

// Library includes
#include <vector>

// Forward declarations
class AbstractTeachingLesson;
class NeuralNetwork;
class AbstractActivationOrder;

// A techer manages many techingLessons
class Teacher
{
private:
	std::vector<std::unique_ptr<AbstractTeachingLesson>> teachingLessons;
public:
	// Adds a new TechingLessont to the teachingLessons list
	void addTeachingLesson(AbstractTeachingLesson* newTeachingLesson);
	// Get all techingLessons (Useful for online learning)
	std::vector<std::unique_ptr<AbstractTeachingLesson>>* getTeachingLessons();
	// Calculate the total error (Useful for offline learning)
	float getTotalError(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder, float weightDecayfac);
};

#endif