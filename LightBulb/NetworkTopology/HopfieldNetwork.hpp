#pragma once

#ifndef _HOPFIELDNETWORK_H_
#define _HOPFIELDNETWORK_H_

// Libary includes

// Includes
#include "NetworkTopology\FreeNetwork.hpp"

// Forward declarations
class AbstractTeachingLesson;
class Teacher;

// A HopfieldNetwork is 
class HopfieldNetwork : public FreeNetwork
{
private:	
public:
	// Create a new HopfieldNetwork with the given counts
	HopfieldNetwork(unsigned int neuronCount, bool binaryActivationFunction);

};

#endif