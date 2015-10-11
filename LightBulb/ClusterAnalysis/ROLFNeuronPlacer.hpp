#pragma once

#ifndef _ROLFNEURONPLACER_H_
#define _ROLFNEURONPLACER_H_

// Library includes
#include <list>

// Includes
#include "ClusterAnalysis/AbstractNonReliableRBFNeuronPlacer.hpp"

// Forward declarations
class RBFNetwork;
class Teacher;

// This class contains all stuff needed to describe a ROLFNeuronPlacer 
class ROLFNeuronPlacer : public AbstractNonReliableRBFNeuronPlacer
{
protected:
public:
	// Inherited:
	void doPlacing(RBFNetwork &neuralNetwork, Teacher &teacher);
	AbstractRBFNeuronPlacer* getCopy();
};

#endif