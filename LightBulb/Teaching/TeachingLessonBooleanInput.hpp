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
	std::unique_ptr<NeuralNetworkIO<double>> teachingInputLinear;
	// The values we will put into the neural network
	std::unique_ptr<NeuralNetworkIO<double>> teachingPattern;	
protected:
	// Inherited:
	// Converts our boolean teachingInput vector in a double vector depending on the used activationFunction
	NeuralNetworkIO<double>* getTeachingInput(AbstractActivationFunction* activationFunction);
	NeuralNetworkIO<double>* getTeachingPattern();
public:
	TeachingLessonBooleanInput(NeuralNetworkIO<double>* teachingPattern_, NeuralNetworkIO<bool>* teachingInput_);
	// Inherited:
	AbstractTeachingLesson* unfold();
	int getMaxTimeStep();
};

#endif
