#pragma once

#ifndef _AbstractEvolutionObject_H_
#define _AbstractEvolutionObject_H_

// Library includes
#include <vector>
#include <algorithm>
#include <algorithm>
#include <algorithm>
#include <algorithm>
#include <algorithm>
#include <algorithm>

// Forward declarations
class EvolutionLearningRule;
class AbstractNeuralNetwork;

enum EvolutionSource
{
	Creation,
	Mutation,
	Recombination,
	Reuse
};

// This class describes an abstract object which "lives" inside an evolution world.
// The evolution object contains a NN which should calculate the actions from external and internal inputs.
class AbstractEvolutionObject 
{
	template <class Archive>
	friend void save(Archive& archive, AbstractEvolutionObject const& object);
	template <class Archive>
	friend void load(Archive& archive, AbstractEvolutionObject& object);
protected:
	// This vector describes the mutation strength of every edge in the NN.
	// It can be used inside the mutation/recombination algorithm
	std::vector<double> mutationStrength;

	EvolutionSource evolutionSource;
	// Resize the mutation strength vector
	void resizeMutationStrength(int newSize);
	// Randomize all values inside the mutation strength vecor
	void randomizeMutationStrength();
public:	
	virtual ~AbstractEvolutionObject() {}
	virtual void copyPropertiesFrom(AbstractEvolutionObject* notUsedObject);
	virtual AbstractNeuralNetwork* getNeuralNetwork() = 0;
	virtual std::vector<double>* getMutationStrength();
	virtual void setMutationStrength(std::vector<double>* newMutationStrength);
	// This method should execute one NN calculation. (Mostly: Get input -> let the NN calculate -> react depending on the NN output)
	virtual void doNNCalculation() = 0;
	// Reset the NN (All activations to zero)
	virtual void resetNN() = 0;
	// This method should return a new evolution object which contains a NN which has the same edges/neurons as the NN of this object.
	virtual AbstractEvolutionObject* clone(bool addToWorld = true) = 0;

	virtual void setEvolutionSource(EvolutionSource evolutionSource_);

	EvolutionSource getEvolutionSource();

	virtual void removeNeuron(int layerIndex, int neuronIndex);

	virtual void addNeuron(int layerIndex);
};

#include "IO/AbstractEvolutionObjectIO.hpp"

#endif
