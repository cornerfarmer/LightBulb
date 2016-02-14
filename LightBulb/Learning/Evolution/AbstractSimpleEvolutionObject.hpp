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

// This class is simplification of the AbstractEvolutionObject class.
// It decreases the work you have to do for your evolutionObject class, but also decreases your possibilities.
// Nevertheless this class can be used in the most of all cases.
class AbstractSimpleEvolutionObject : public AbstractEvolutionObject
{
protected:
	// The NN of the object
	NeuralNetwork* neuralNetwork;
	// The world which holds this object
	AbstractEvolutionWorld* world;
	// This method should return the input for the neural network
	virtual void getNNInput(std::vector<double>& input) = 0;
	// This method should interpret and act depending on the given NN output
	virtual void interpretNNOutput(std::vector<double>& output) = 0;
public:	
	// Create a new evolution object with the given input and output NN size
	AbstractSimpleEvolutionObject(AbstractEvolutionWorld* world, int inputDimension, int outputDimension);
	~AbstractSimpleEvolutionObject();
	// Inherited:
	void doNNCalculation();
	NeuralNetwork* getNeuralNetwork();
	void resetNN();
	AbstractEvolutionObject* clone(bool addToWorld = true);
};
#endif
