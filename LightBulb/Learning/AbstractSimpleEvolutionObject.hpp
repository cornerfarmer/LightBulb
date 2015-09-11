#pragma once

#ifndef _ABSTRACTSIMPLEEVOLUTIONOBJECT_H_
#define _ABSTRACTSIMPLEEVOLUTIONOBJECT_H_

// Library Includes
#include <memory>

// Includes
#include "Learning\EvolutionObjectInterface.hpp"
#include "NeuralNetwork\NeuralNetworkIO.hpp"

// Forward declarations
class EvolutionLearningRule;
class NeuralNetwork;
class RecurrentLayeredNetworkOptions;
class EvolutionWorldInterface; 

class AbstractSimpleEvolutionObject : public EvolutionObjectInterface
{
private:
protected:
	NeuralNetwork* neuralNetwork;
	EvolutionWorldInterface* world;
	virtual NeuralNetworkIO<double> getNNInput() = 0;
	virtual void interpretNNOutput(EvolutionLearningRule& learningRule, NeuralNetworkIO<double>* output) = 0;
public:	
	AbstractSimpleEvolutionObject(EvolutionWorldInterface* world, int inputDimension, int outputDimension);
	~AbstractSimpleEvolutionObject();
	void doNNCalculation(EvolutionLearningRule& learningRule);
	NeuralNetwork* getNeuralNetwork();
	void resetNN();
	EvolutionObjectInterface* clone();
};
#endif