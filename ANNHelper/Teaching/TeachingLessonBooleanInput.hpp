#pragma once

#ifndef _TEACHINGLESSONBOOLEANINPUT_H_
#define _TEACHINGLESSONBOOLEANINPUT_H_

// Library Includes
#include <vector>
#include <list>

// Includes
#include "Teaching\AbstractTeachingLesson.hpp"

// Forward declarations

class TeachingLessonBooleanInput : public AbstractTeachingLesson
{
private:
	// The values the neural network should give back
	std::unique_ptr<NeuralNetworkIO<bool>> teachingInput;
	std::unique_ptr<NeuralNetworkIO<float>> teachingInputLinear;
	// The values we will put into the neural network
	std::unique_ptr<NeuralNetworkIO<float>> teachingPattern;	
protected:
	// Inherited:
	// Converts our boolean teachingInput vector in a float vector depending on the used activationFunction
	NeuralNetworkIO<float>* getTeachingInput(AbstractActivationFunction* activationFunction);
	NeuralNetworkIO<float>* getTeachingPattern();
public:
	TeachingLessonBooleanInput(NeuralNetworkIO<float>* teachingPattern_, NeuralNetworkIO<bool>* teachingInput_);
	// Inherited:
	AbstractTeachingLesson* unfold();
	int getMaxTimeStep();
};

#endif

