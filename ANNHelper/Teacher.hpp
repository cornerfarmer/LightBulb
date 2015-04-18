#pragma once

#ifndef _TEACHER_H_
#define _TEACHER_H_

// Library includes
#include <vector>

// Forward declarations
class TeachingLesson;
class NeuralNetwork;
class ActivationOrder;

// A techer manages many techingLessons
class Teacher
{
private:
	std::vector<TeachingLesson*> teachingLessons;
public:
	// Adds a new TechingLessont to the teachingLessons list
	void addTeachingLesson(TeachingLesson* newTeachingLesson);
	// Get all techingLessons (Useful for online learning)
	std::vector<TeachingLesson*>* getTeachingLessons();
	// Calculate the total error (Useful for offline learning)
	float getTotalError(NeuralNetwork &neuralNetwork, ActivationOrder &activationOrder);
};

#endif