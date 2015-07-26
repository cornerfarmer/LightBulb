#pragma once

#ifndef _LVQNETWORK_H_
#define _LVQNETWORK_H_

// Libary includes

// Includes
#include "NetworkTopology\LayeredNetwork.hpp"

// Forward declarations
class AbstractTeachingLesson;

// A LVQNetwork is layered network which has only one input and one output layer.
class LVQNetwork : public LayeredNetwork
{
private:	
public:
	// Create a new CascadeCorrelationNetwork with the given counts
	LVQNetwork(unsigned int inputNeuronCount, unsigned int codebookVectorCount, unsigned int classCount);

	int getClassCount();

	int getCodebookVectorCount();

	int getClassOfNeuron(AbstractNeuron* neuron);

	int getClassOfNeuronWithIndex(int neuronIndex);

	int getClassOfTeachingLesson(AbstractTeachingLesson& teachingLesson);

	void divideCodebookVectorsIntoClasses();
};

#endif