#pragma once

#ifndef _TEACHINGLESSONLINEARINPUT_H_
#define _TEACHINGLESSONLINEARINPUT_H_

// Library Includes
#include <vector>

// Includes
#include "Teaching/AbstractTeachingLesson.hpp"

// Forward declarations

class TeachingLessonLinearInput : public AbstractTeachingLesson
{
private:
	// The values the neural network should give back
	std::unique_ptr<NeuralNetworkIO<double>> teachingInput;
	// The values we will put into the neural network
	std::unique_ptr<NeuralNetworkIO<double>> teachingPattern;
protected:	
	// Inherited:
	NeuralNetworkIO<double>* getTeachingInput(AbstractActivationFunction* activationFunction);
	NeuralNetworkIO<double>* getTeachingPattern();
public:
	TeachingLessonLinearInput(NeuralNetworkIO<double>* teachingPattern_, NeuralNetworkIO<double>* teachingInput_);
	// Inherited:
	AbstractTeachingLesson* unfold();
	int getMaxTimeStep();
};

#endif

