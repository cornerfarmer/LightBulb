#pragma once

#ifndef _EVOLUTIONOBJECTINTERFACE_H_
#define _EVOLUTIONOBJECTINTERFACE_H_

// Library Includes
#include <vector>

// Forward declarations
class EvolutionLearningRule;
class NeuralNetwork;

class EvolutionObjectInterface 
{
protected:
	
public:	
	virtual void doNNCalculation(EvolutionLearningRule& learningRule) = 0;
	virtual void resetNN() = 0;
	virtual NeuralNetwork* getNeuralNetwork() = 0;
	virtual ~EvolutionObjectInterface() {};
	virtual EvolutionObjectInterface* clone() = 0;
	virtual std::vector<double>* getMutationStrength() = 0;
};
#endif