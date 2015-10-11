#pragma once

#ifndef _LVQNETWORK_H_
#define _LVQNETWORK_H_

// Libary includes

// Includes
#include "NetworkTopology/LayeredNetwork.hpp"

// Forward declarations
class AbstractTeachingLesson;
class Teacher;

// A LVQNetwork is layered network which has only one input, one hidden and one output layer.
class LVQNetwork : public LayeredNetwork
{
private:	
public:
	// Create a new LVQNetwork with the given counts
	LVQNetwork(unsigned int inputNeuronCount, unsigned int codebookVectorCount, unsigned int classCount);
	// Returns the count of all classes
	int getClassCount();
	// Returns the count of all codebook vectors
	int getCodebookVectorCount();
	// Returns the class of a neuron in the hidden layer
	int getClassOfNeuron(AbstractNeuron* neuron);
	// Returns the class of a neuron with the given index in the hidden layer
	int getClassOfNeuronWithIndex(int neuronIndex);
	// Returns the class of a teaching lesson
	int getClassOfTeachingLesson(AbstractTeachingLesson& teachingLesson);
	// Divide the codebook vectors into classes (not random)
	void divideCodebookVectorsIntoClasses();
	// Place all codebook vectors in the hidden layer on teaching lessons (random)
	void placeCodebookVectorsOnTeachingLessons(Teacher& teacher);
};

#endif