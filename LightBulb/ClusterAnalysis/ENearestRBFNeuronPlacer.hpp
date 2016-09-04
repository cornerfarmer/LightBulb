#pragma once

#ifndef _ENEARESTRBFNEURONPLACER_H_
#define _ENEARESTRBFNEURONPLACER_H_

// Library includes
#include <list>

// Includes
#include "ClusterAnalysis/AbstractNonReliableRBFNeuronPlacer.hpp"

// Forward declarations
class RBFNetwork;
class Teacher;

// This class contains all stuff needed to describe a RBFNeuronPlacer 
class ENearestRBFNeuronPlacer : public AbstractNonReliableRBFNeuronPlacer
{
protected:
	// Sets the minimum cluster width
	static const double iterationEndPrecision;
public:
	void doPlacing(RBFNetwork &neuralNetwork, Teacher &teacher) override;
	AbstractRBFNeuronPlacer* getCopy() override;
};

#endif