#pragma once

#ifndef _ABSTRACTSIMPLEEVOLUTIONOBJECT_H_
#define _ABSTRACTSIMPLEEVOLUTIONOBJECT_H_

// Library Includes
#include <memory>

// Includes
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "NeuralNetwork/NeuralNetworkIO.hpp"

// Forward declarations
class EvolutionLearningRule;
class NeuralNetwork;
class RecurrentLayeredNetworkOptions;
class AbstractEvolutionWorld; 

class AbstractSimpleEvolutionObject : public AbstractEvolutionObject
{
private:
protected:
	NeuralNetwork* neuralNetwork;
	AbstractEvolutionWorld* world;
	virtual NeuralNetworkIO<double> getNNInput() = 0;
	virtual void interpretNNOutput(EvolutionLearningRule& learningRule, NeuralNetworkIO<double>* output) = 0;
public:	
	AbstractSimpleEvolutionObject(AbstractEvolutionWorld* world, int inputDimension, int outputDimension, bool biasNeuron = true);
	~AbstractSimpleEvolutionObject();
	void doNNCalculation(EvolutionLearningRule& learningRule);
	NeuralNetwork* getNeuralNetwork();
	void resetNN();
	AbstractEvolutionObject* clone();
};
#endif
