#pragma once

#ifndef _ABSTRACTTEACHER_H_
#define _ABSTRACTTEACHER_H_

// Includes

// Library includes
#include <vector>
#include <memory>

// Forward declarations
class AbstractNeuralNetwork;
class AbstractActivationOrder;
class AbstractTeachingLesson;

class AbstractTeacher
{
private:
public:
	// Adds a new TechingLesson to the teachingLessons list
	virtual void addTeachingLesson(AbstractTeachingLesson* newTeachingLesson) = 0;
	// Adds a new TechingLesson to the testingLessons list
	virtual void addTestingLesson(AbstractTeachingLesson* newTestingLesson) = 0;
	// Get all techingLessons (Useful for online learning)
	virtual std::vector<std::unique_ptr<AbstractTeachingLesson>>* getTeachingLessons() = 0;

	virtual std::vector<std::unique_ptr<AbstractTeachingLesson>>* getTestingLessons() = 0;
	// Calculate the total error from all teaching and testing lessons (Useful for offline learning)
	virtual double getTotalError(AbstractNeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder) = 0;
	// Returns a unfolded version of this teacher
	virtual AbstractTeacher* unfold() = 0;
	// Returns the biggest used timestep of all teaching lessons
	virtual int getMaxTimeStep() = 0;

};

#endif
