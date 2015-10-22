#pragma once

#ifndef _AbstractEvolutionObject_H_
#define _AbstractEvolutionObject_H_

// Library Includes
#include <vector>

// Forward declarations
class EvolutionLearningRule;
class NeuralNetwork;

class AbstractEvolutionObject 
{
protected:
	std::vector<double> mutationStrength;
	void resizeMutationStrength(int newSize);
	void randomizeMutationStrength();
public:	
	virtual void doNNCalculation(EvolutionLearningRule& learningRule) = 0;
	virtual void resetNN() = 0;
	virtual NeuralNetwork* getNeuralNetwork() = 0;
	virtual ~AbstractEvolutionObject() {};
	virtual AbstractEvolutionObject* clone() = 0;
	virtual std::vector<double>* getMutationStrength();
	virtual void setMutationStrength(std::vector<double>* newMutationStrength);
};
#endif
