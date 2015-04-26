#pragma once

#ifndef _TEACHINGLESSONLINEARINPUT_H_
#define _TEACHINGLESSONLINEARINPUT_H_

// Library Includes
#include <vector>

// Includes
#include "AbstractTeachingLesson.hpp"

class TeachingLessonLinearInput : public AbstractTeachingLesson
{
private:
	// The values the neural network should give back
	std::vector<float>* teachingInput;
	// The values we will put into the neural network
	std::vector<float>* teachingPattern;
protected:	
	std::vector<float>* getTeachingInput(AbstractActivationFunction* activationFunction);
	std::vector<float>* getTeachingPattern();
public:
	~TeachingLessonLinearInput();
	TeachingLessonLinearInput(std::vector<float>* teachingPattern_, std::vector<float>* teachingInput_);
};

#endif

