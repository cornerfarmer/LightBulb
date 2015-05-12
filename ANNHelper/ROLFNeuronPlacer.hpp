#pragma once

#ifndef _ROLFNEURONPLACER_H_
#define _ROLFNEURONPLACER_H_

// Library includes
#include <list>

// Includes
#include "AbstractNonReliableRBFNeuronPlacer.hpp"

// Forward declarations
class RBFNetwork;
class Teacher;

// This class contains all stuff needed to describe a RBFNeuronPlacer 
class ROLFNeuronPlacer : public AbstractNonReliableRBFNeuronPlacer
{
protected:
public:
	void doPlacing(RBFNetwork &neuralNetwork, Teacher &teacher);
	AbstractRBFNeuronPlacer* getCopy();
};

#endif