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

// A evolution object used in the TeachingEvolutionWorld
class TeachedEvolutionObject : public AbstractEvolutionObject
{
protected:
	// The corresponding world
	TeachingEvolutionWorld* teachingEvolutionWorld;
	// The used network
	NeuralNetwork* neuralNetwork;
	// The currentTotalError (used as score)
	double currentTotalError;
public:	
	// Create a new evolution object in the given world and with a NN built after the given network options
	TeachedEvolutionObject(TeachingEvolutionWorld* teachingEvolutionWorld_, LayeredNetworkOptions& options);
	~TeachedEvolutionObject();
	double getCurrentTotalError();
	// Inherited:
	void doNNCalculation();
	void resetNN();
	NeuralNetwork* getNeuralNetwork();
	AbstractEvolutionObject* clone(bool addToWorld = true);
};
#endif
