#pragma once

#ifndef _KMEANSRBFNEURONPLACER_H_
#define _KMEANSRBFNEURONPLACER_H_

// Library includes

// Includes
#include "AbstractRBFNeuronPlacer.hpp"

// Forward declarations
class RBFNetwork;
class Teacher;

// This class contains all stuff needed to describe a RBFNeuronPlacer 
class KMeansRBFNeuronPlacer : public AbstractRBFNeuronPlacer
{
protected:
public:
	void doPlacing(RBFNetwork &neuralNetwork, Teacher &teacher);
	AbstractRBFNeuronPlacer* getCopy();
};

#endif