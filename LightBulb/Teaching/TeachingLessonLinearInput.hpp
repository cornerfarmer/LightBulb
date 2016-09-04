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
	std::vector<std::vector<double>> teachingPattern;
protected:	
	std::vector<std::vector<double>> unfoldTeachingPattern();
public:
	TeachingLessonLinearInput(std::vector<std::vector<double>> teachingPattern_, NeuralNetworkIO<double>* teachingInput_);
	// Inherited:
	AbstractTeachingLesson* unfold() override;
	int getMaxTimeStep() override;
	NeuralNetworkIO<double>* getTeachingInput(AbstractActivationFunction* activationFunction) override;
	std::vector<std::vector<double>>* getTeachingPattern() override;
};

#endif

