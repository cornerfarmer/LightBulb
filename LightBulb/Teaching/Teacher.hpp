#pragma once

#ifndef _TEACHER_H_
#define _TEACHER_H_

// Includes
#include "AbstractTeachingLesson.hpp"
#include "AbstractTeacher.hpp"

// Library includes

// Forward declarations

// A teacher manages many teachingLessons
class Teacher : public AbstractTeacher
{
private:
	double weightDecayFac;
	// A list of teaching lessons which are used for total error calculation and learning stuff
	std::vector<std::unique_ptr<AbstractTeachingLesson>> teachingLessons;
	// A list of teaching lessons which influent the total error, but they will not be part of any learning process
	std::vector<std::unique_ptr<AbstractTeachingLesson>> testingLessons;
public:
	Teacher(double weightDecayFac_ = 0);
	// Adds a new TechingLesson to the teachingLessons list
	void addTeachingLesson(AbstractTeachingLesson* newTeachingLesson) override;
	// Adds a new TechingLesson to the testingLessons list
	void addTestingLesson(AbstractTeachingLesson* newTestingLesson) override;
	// Get all techingLessons (Useful for online learning)
	std::vector<std::unique_ptr<AbstractTeachingLesson>>* getTeachingLessons() override;

	std::vector<std::unique_ptr<AbstractTeachingLesson>>* getTestingLessons() override;
	// Calculate the total error from all teaching and testing lessons (Useful for offline learning)
	double getTotalError(AbstractNeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder) override;

	double getTeachingError(AbstractNeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder) override;

	double getWeightDecayError(AbstractNeuralNetwork &neuralNetwork) override;
	// Returns a unfolded version of this teacher
	AbstractTeacher* unfold() override;
	// Returns the biggest used timestep of all teaching lessons
	int getMaxTimeStep() override;

};

#endif
