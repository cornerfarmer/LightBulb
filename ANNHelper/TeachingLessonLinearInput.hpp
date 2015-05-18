#pragma once

#ifndef _TEACHINGLESSONLINEARINPUT_H_
#define _TEACHINGLESSONLINEARINPUT_H_

// Library Includes
#include <vector>

// Includes
#include "AbstractTeachingLesson.hpp"

// Forward declarations
class NeuralNetworkIO;

class TeachingLessonLinearInput : public AbstractTeachingLesson
{
private:
	// The values the neural network should give back
	std::unique_ptr<std::vector<float>> teachingInput;
	// The values we will put into the neural network
	std::unique_ptr<NeuralNetworkIO> teachingPattern;
protected:	
	std::vector<float>* getTeachingInput(AbstractActivationFunction* activationFunction);
	NeuralNetworkIO* getTeachingPattern();
public:
	TeachingLessonLinearInput(NeuralNetworkIO* teachingPattern_, std::vector<float>* teachingInput_);
};

#endif

