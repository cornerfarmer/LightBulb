#pragma once

#ifndef _TEACHINGLESSONBOOLEANINPUT_H_
#define _TEACHINGLESSONBOOLEANINPUT_H_

// Library Includes
#include <vector>
#include <list>

// Includes
#include "Teaching/AbstractTeachingLesson.hpp"

// Forward declarations

class TeachingLessonBooleanInput : public AbstractTeachingLesson
{
private:
	// The values the neural network should give back
	std::unique_ptr<NeuralNetworkIO<bool>> teachingInput;
	std::unique_ptr<NeuralNetworkIO<double>> teachingInputLinear;
	// The values we will put into the neural network
	std::vector<std::vector<double>> teachingPattern;
	bool calcStrictError;
protected:
	std::vector<std::vector<double>> unfoldTeachingPattern();
public:
	TeachingLessonBooleanInput(std::vector<std::vector<double>> teachingPattern_, NeuralNetworkIO<bool>* teachingInput_, bool calcStrictError_ = true);
	// Inherited:
	AbstractTeachingLesson* unfold() override;
	int getMaxTimeStep() override;
	// Converts our boolean teachingInput vector in a double vector depending on the used activationFunction
	NeuralNetworkIO<double>* getTeachingInput(AbstractActivationFunction* activationFunction) override;
	NeuralNetworkIO<bool>* getBooleanTeachingInput();
	std::vector<std::vector<double>>* getTeachingPattern() override;

	std::unique_ptr<ErrorMap_t> getErrormapFromOutputVector(std::vector<std::vector<double>>& outputVector, AbstractNeuralNetwork& neuralNetwork);
};

#endif

