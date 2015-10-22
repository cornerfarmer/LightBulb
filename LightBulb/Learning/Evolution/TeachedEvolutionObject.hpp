#pragma once

#ifndef _TEACHEDEVOLUTIONOBJECT_H_
#define _TEACHEDEVOLUTIONOBJECT_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractEvolutionObject.hpp"

// Forward declarations
class EvolutionLearningRule;
class TeachingEvolutionWorld;
class NeuralNetwork;
class LayeredNetworkOptions;

class TeachedEvolutionObject : public AbstractEvolutionObject
{
protected:
	TeachingEvolutionWorld* teachingEvolutionWorld;
	NeuralNetwork* neuralNetwork;
	double currentTotalError;
public:	
	TeachedEvolutionObject(TeachingEvolutionWorld* teachingEvolutionWorld_, LayeredNetworkOptions& options);
	~TeachedEvolutionObject();
	void doNNCalculation(EvolutionLearningRule& learningRule);
	void resetNN();
	NeuralNetwork* getNeuralNetwork();
	AbstractEvolutionObject* clone();
	double getCurrentTotalError();
};
#endif
