#pragma once

#ifndef _EVOLUTIONOBJECTINTERFACE_H_
#define _EVOLUTIONOBJECTINTERFACE_H_

// Library Includes

// Forward declarations
class EvolutionLearningRule;
class NeuralNetwork;


class EvolutionObjectInterface 
{
protected:
	
public:	
	virtual void doNNCalculation(EvolutionLearningRule& learningRule) = 0;
	virtual NeuralNetwork* getNeuralNetwork() = 0;
	virtual ~EvolutionObjectInterface() {};

};
#endif