#pragma once

#ifndef _LVQNETWORK_H_
#define _LVQNETWORK_H_

// Libary includes

// Includes
#include "NetworkTopology\LayeredNetwork.hpp"

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

	int getClassCount();

	int getCodebookVectorCount();

	int getClassOfNeuron(AbstractNeuron* neuron);

	int getClassOfNeuronWithIndex(int neuronIndex);

	int getClassOfTeachingLesson(AbstractTeachingLesson& teachingLesson);

	void divideCodebookVectorsIntoClasses();

	void placeCodebookVectorsOnTeachingLessons(Teacher& teacher);
};

#endif