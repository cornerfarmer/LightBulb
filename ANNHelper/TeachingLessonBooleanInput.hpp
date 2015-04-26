#pragma once

#ifndef _TEACHINGLESSONBOOLEANINPUT_H_
#define _TEACHINGLESSONBOOLEANINPUT_H_

// Library Includes
#include <vector>

// Includes
#include "AbstractTeachingLesson.hpp"

class TeachingLessonBooleanInput : public AbstractTeachingLesson
{
private:
	// The values the neural network should give back
	std::vector<bool>* teachingInput;
	std::vector<float>* teachingInputLinear;
	// The values we will put into the neural network
	std::vector<float>* teachingPattern;	
protected:
	// Converts our boolean teachingInput vector in a float vector depending on the used activationFunction
	std::vector<float>* getTeachingInput(AbstractActivationFunction* activationFunction);
	std::vector<float>* getTeachingPattern();
public:
	~TeachingLessonBooleanInput();
	TeachingLessonBooleanInput(std::vector<float>* teachingPattern_, std::vector<bool>* teachingInput_);
};

#endif

