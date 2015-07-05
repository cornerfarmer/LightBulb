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
	// A list of teaching lessons which are used for total error calculation and learning stuff
	std::vector<std::unique_ptr<AbstractTeachingLesson>> teachingLessons;
	// A list of teaching lessons which influent the total error, but they will not be part of any learning process
	std::vector<std::unique_ptr<AbstractTeachingLesson>> testingLessons;
public:
	// Adds a new TechingLesson to the teachingLessons list
	void addTeachingLesson(AbstractTeachingLesson* newTeachingLesson);
	// Adds a new TechingLesson to the testingLessons list
	void addTestingLesson(AbstractTeachingLesson* newTestingLesson);
	// Get all techingLessons (Useful for online learning)
	std::vector<std::unique_ptr<AbstractTeachingLesson>>* getTeachingLessons();
	// Calculate the total error from all teaching and testing lessons (Useful for offline learning)
	float getTotalError(NeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder);
	// Returns a unfolded version of this teacher
	std::unique_ptr<Teacher> unfold();
	// Returns the biggest used timestep of all teaching lessons
	int getMaxTimeStep();
};

#endif