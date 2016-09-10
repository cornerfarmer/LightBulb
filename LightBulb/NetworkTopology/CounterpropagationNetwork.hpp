#pragma once

#ifndef _COUNTERPROPAGATIONNETWORK_H_
#define _COUNTERPROPAGATIONNETWORK_H_

// Libary includes

// Includes
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractTeachingLesson;
	class Teacher;

	// A CounterpropagationNetwork is layered network which has only one input, one hidden and one output layer.
	class CounterpropagationNetwork : public FeedForwardNetworkTopology
	{
	private:
	public:
		// Create a new CounterpropagationNetwork with the given counts
		CounterpropagationNetwork(unsigned int inputNeuronCount, unsigned int codebookVectorCount, unsigned int outputNeuronCount);
		// Place all codebook vectors in the hidden layer on teaching lessons (random)
		void placeCodebookVectorsOnTeachingLessons(Teacher& teacher);
	};
}

#endif