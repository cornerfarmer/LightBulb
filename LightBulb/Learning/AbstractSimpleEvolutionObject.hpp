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
	std::vector<double> mutationStrength;
	NeuralNetwork* neuralNetwork;
	EvolutionWorldInterface* world;
	void randomizeMutationStrength();
	virtual NeuralNetworkIO<double> getNNInput() = 0;
	virtual void interpretNNOutput(EvolutionLearningRule& learningRule, NeuralNetworkIO<double>* output) = 0;
public:	
	AbstractSimpleEvolutionObject(EvolutionWorldInterface* world, int inputDimension, int outputDimension, bool biasNeuron = true);
	~AbstractSimpleEvolutionObject();
	void doNNCalculation(EvolutionLearningRule& learningRule);
	NeuralNetwork* getNeuralNetwork();
	void resetNN();
	EvolutionObjectInterface* clone();
	std::vector<double>* getMutationStrength();
};
#endif