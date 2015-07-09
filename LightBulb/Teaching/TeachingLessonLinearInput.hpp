#pragma once

#ifndef _TEACHINGLESSONLINEARINPUT_H_
#define _TEACHINGLESSONLINEARINPUT_H_

// Library Includes
#include <vector>

// Includes
#include "Teaching\AbstractTeachingLesson.hpp"

// Forward declarations

class TeachingLessonLinearInput : public AbstractTeachingLesson
{
private:
	// The values the neural network should give back
	std::unique_ptr<NeuralNetworkIO<float>> teachingInput;
	// The values we will put into the neural network
	std::unique_ptr<NeuralNetworkIO<float>> teachingPattern;
protected:	
	// Inherited:
	NeuralNetworkIO<float>* getTeachingInput(AbstractActivationFunction* activationFunction);
	NeuralNetworkIO<float>* getTeachingPattern();
public:
	TeachingLessonLinearInput(NeuralNetworkIO<float>* teachingPattern_, NeuralNetworkIO<float>* teachingInput_);
	// Inherited:
	AbstractTeachingLesson* unfold();
	int getMaxTimeStep();
};

#endif

